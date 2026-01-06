//
// Created by Harry Skerritt on 18/12/2025.
//

#include "spotify/auth/Auth.hpp"

#include "spotify/core/Errors.hpp"
#include "spotify/core/Endpoints.hpp"


namespace Spotify {

    Auth::Auth(const ClientCredentials& keys) {
        if (keys.client_id.empty() || keys.client_secret.empty()) {
            throw LogicException("ClientCredentials cannot be empty");
        }
        m_credentials = keys;
    }

    std::string Auth::createAuthoriseURL(
        const std::string& redirect_uri,
        const std::vector<Scope>& scopes,
        const std::optional<std::string>& state)
    {
        if (redirect_uri.empty()) throw LogicException("Redirect URI cannot be empty.");

        std::string scope_str = buildScopeString(scopes);
        auto actual_state = state.value_or(detail::generateRandomState());
        m_redirectUri = redirect_uri;

        std::ostringstream oss;
        oss << "?response_type=code"
        << "&client_id=" << detail::urlEncode(m_credentials.client_id)
        << "&scope=" << detail::urlEncode(scope_str)
        << "&redirect_uri=" << detail::urlEncode(redirect_uri)
        << "&state=" << detail::urlEncode(actual_state);

        return Endpoints::AUTHORISE + oss.str();
    }

    void Auth::exchangeCode(const std::string &code) {
        if (code.empty()) throw LogicException("Authorization Code cannot be empty.");

        std::ostringstream post_fields;
        post_fields << "code=" << detail::urlEncode(code)
                    << "&redirect_uri=" << detail::urlEncode(m_redirectUri)
                    << "&grant_type=authorization_code";

        HTTP::HeaderMap headers;
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        headers["Authorization"] = "Basic " + encodeClientCredentials();

        auto result = HTTP::post(Endpoints::TOKEN, "", post_fields.str(), headers, true);
        ErrorHandler::verifyResponse(result);

        buildAuthResponse(result.body);
    }

    void Auth::refreshAccessToken(const std::optional<std::string>& refresh_token) {
        std::string token = refresh_token.value_or(m_refresh_token);
        if (token.empty()) throw LogicException("No refresh token available");

        std::string body = "grant_type=refresh_token&refresh_token=" + detail::urlEncode(token);

        HTTP::HeaderMap headers;
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        headers["Authorization"] = "Basic " + encodeClientCredentials();


        auto result = HTTP::post(Endpoints::TOKEN, "", body, headers);
        ErrorHandler::verifyResponse(result);

        buildAuthResponse(result.body);
    }

    bool Auth::begin(const std::string& refresh_token) {
        if (refresh_token.empty()) return false;

        m_refresh_token = refresh_token;

        try {
            refreshAccessToken();
            return true;

        } catch (const Spotify::Exception& e) {
            std::cerr << "Could not validate refresh token" << std::endl;
            return false;
        }
    }

    // Getters
    std::string Auth::getAccessToken() {
        if (isTokenExpired()) {
            refreshAccessToken();
        }
        return m_authResponse.access_token;
    }

    std::string Auth::getRefreshToken() {
        return m_refresh_token;
    }


    // --- PRIVATE ---
    AuthResponse Auth::buildAuthResponse(const std::string &json) {
        try {
            auto data = nlohmann::json::parse(json);
            AuthResponse response;

            response.access_token = data.at("access_token").get<std::string>();
            response.token_type   = data.at("token_type").get<std::string>();
            response.scope        = data.at("scope").get<std::string>();

            int expires_in = data.at("expires_in").get<int>();
            response.expire_time = std::chrono::system_clock::now() + std::chrono::seconds(expires_in);

            if (data.contains("refresh_token")) {
                m_refresh_token = data.at("refresh_token").get<std::string>();
                response.refresh_token = m_refresh_token;
            } else {
                // Keep the existing refresh token if a new one wasn't sent
                response.refresh_token = m_refresh_token;
            }

            response.response_code = HTTPStatus_Code::OK;
            m_authResponse = response;
            return response;
        } catch (const nlohmann::json::exception &e) {
            throw Spotify::ParseException("Failed to build AuthResponse: " + std::string(e.what()), json);
        }
    }

    // HELPERS
    std::string Auth::encodeClientCredentials() const {
        std::string client_creds = m_credentials.client_id + ":" +  m_credentials.client_secret;
        std::string encoded = base64_encode(client_creds);
        return encoded;
    }

    bool Auth::isTokenExpired() const {
        return std::chrono::system_clock::now() >= m_authResponse.expire_time;
    }
}



