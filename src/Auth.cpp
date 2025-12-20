//
// Created by Harry Skerritt on 18/12/2025.
//

#include <iostream>
#include "spotify/Auth.hpp"
#include "spotify/base64.hpp"

// CURL Helper
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



Spotify::Auth::Auth(Client keys) {
    m_keys = std::move(keys);
}

std::string Spotify::Auth::getAuthURL(
    const std::string& redirect_uri,
    const std::vector<std::string>& scopes,
    const std::optional<std::string> state)
{

    // Make scopes one string
    std::ostringstream scope_stream;
    for (size_t i = 0; i < scopes.size(); ++i) {
        if (i > 0) scope_stream << " ";
        scope_stream << scopes[i];
    }

    auto actual_state = state.value_or(WebTools::generateRandomState());

    m_redirectUri = redirect_uri;

    std::ostringstream oss;
    oss << "response_type=code"
    << "&client_id=" << WebTools::urlEncode(m_keys.client_id)
    << "&scope=" << WebTools::urlEncode(scope_stream.str())
    << "&redirect_uri=" << WebTools::urlEncode(redirect_uri)
    << "&state=" << WebTools::urlEncode(actual_state);

    std::string auth_url = "https://accounts.spotify.com/authorize?"+ oss.str();

    return auth_url;
}

Spotify::AuthResponse Spotify::Auth::getAuthToken(const std::string &code) {

    AuthResponse response;

    CURL *curl;
    CURLcode result;
    curl_slist *headers = NULL;

#if WIN32
    result = curl_global_init(CURL_GLOBAL_ALL);
    if (result)
        return (int) result;
#endif

    // Post Fields
    std::ostringstream post_fields;
    post_fields << "code=" << WebTools::urlEncode(code)
                << "&redirect_uri=" << WebTools::urlEncode(m_redirectUri)
                << "&grant_type=authorization_code";
    std::string body_str = post_fields.str();


    // Auth Header
    std::string auth_header = "Authorization: Basic " + encodeClientCreds();

    long http_code = 0;
    std::string response_str;

    curl = curl_easy_init();
    if (curl) {
        // Setting headers
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, auth_header.c_str());


        curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body_str.length());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

        result = curl_easy_perform(curl);

        // Handle a CURL error - Network Level
        if (result != CURLE_OK) {
            response.response_code = NETWORK_ERROR;
            curl_easy_cleanup(curl);
            return response;
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
#if WIN32
    curl_global_cleanup();
#endif

    // API bad response
    if (http_code != 200) {
        response.response_code = AUTH_ERROR;
        return response;
    }

    // API Good response
    response = buildAuthResponse(response_str);
    return response;
}

Spotify::AuthResponse Spotify::Auth::refreshAuthToken(const std::optional<std::string>& refresh_token) {
    AuthResponse response;

    CURL *curl;
    CURLcode result;
    curl_slist *headers = NULL;

    if (!refresh_token.has_value() && m_refresh_token.empty()) {
        // No refresh token - error
        response.response_code = VALUE_ERROR;
        return response;
    }

#if WIN32
    result = curl_global_init(CURL_GLOBAL_ALL);
    if (result)
        return (int) result;
#endif

    // Post Fields
    std::ostringstream post_fields;
    post_fields << "grant_type=refresh_token"
                << "&refresh_token=" << WebTools::urlEncode(refresh_token.value_or(m_refresh_token))
                << "&client_id=" << WebTools::urlEncode(m_keys.client_id);
    std::string body_str = post_fields.str();

    std::string auth_header = "Authorization: Basic " + encodeClientCreds();

    long http_code = 0;
    std::string response_str;

    curl = curl_easy_init();
    if (curl) {
        // Setting headers
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        headers = curl_slist_append(headers, auth_header.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body_str.length());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

        result = curl_easy_perform(curl);

        // Handle a CURL error - Network Level
        if (result != CURLE_OK) {
            response.response_code = NETWORK_ERROR;
            curl_easy_cleanup(curl);
            return response;
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
#if WIN32
    curl_global_cleanup();
#endif

    // API bad response
    if (http_code != 200) {
        response.response_code = AUTH_ERROR;
        std::cerr << "CURL Response: " << response_str << std::endl;
        return response;
    }

    // API Good response
    response = buildAuthResponse(response_str);
    return response;
}


// Helpers


Spotify::AuthResponse Spotify::Auth::buildAuthResponse(const std::string &json) {
    AuthResponse response;

    // API good response
    response.access_token = WebTools::extractValue(json, "access_token");
    response.token_type = WebTools::extractValue(json, "token_type");
    response.scope = WebTools::extractValue(json, "scope");
    response.expires_in = WebTools::extractIntValue(json, "expires_in");
    m_refresh_token = WebTools::extractValue(json, "refresh_token");
    response.refresh_token = m_refresh_token;



    if (response.access_token.empty()) {
        response.response_code = PARSE_ERROR;
    } else {
        response.response_code = SUCCESS;
    }

    return response;
}

std::string Spotify::Auth::encodeClientCreds() const {
    std::string client_creds = m_keys.client_id + ":" +  m_keys.client_secret;
    std::string encoded = base64_encode(client_creds);
    return encoded;
}
