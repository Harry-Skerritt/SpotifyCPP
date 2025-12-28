//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/util/Http.hpp"

#include <curl/curl.h>

#include "spotify/util/base64.hpp"

namespace Spotify {
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    static curl_slist* prepareHeaders(const std::string& bearer, const HTTP::HeaderMap &extra) {
        curl_slist* headers = NULL;

        std::string auth = "Authorization: Bearer " + bearer;
        headers = curl_slist_append(headers, auth.c_str());
        headers = curl_slist_append(headers, "User-Agent: spotify-cpp-client");

        for (const auto& [key, value] : extra) {
            std::string header_str = key + ": " + value;
            headers = curl_slist_append(headers, header_str.c_str());
        }

        return headers;
    }


    // For API
    HTTP::Result HTTP::get(const std::string &url, const std::string &bearer, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) return result;

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            result.code = Spotify::RFC2616_Code::NETWORK_ERROR;
        } else {
            long status = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            result.code = static_cast<Spotify::RFC2616_Code>(status);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::post(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) return result;

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        if (!body.empty() && extra_headers.find("Content-Type") == extra_headers.end()) {
            headers = curl_slist_append(headers, "Content-Type: application/json");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body.length());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            result.code = Spotify::RFC2616_Code::NETWORK_ERROR;
        } else {
            long status = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            result.code = static_cast<Spotify::RFC2616_Code>(status);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::put(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) return result;

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        if (!body.empty() && extra_headers.find("Content-Type") == extra_headers.end()) {
            headers = curl_slist_append(headers, "Content-Type: application/json");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        if (!body.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body.length());
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            result.code = Spotify::RFC2616_Code::NETWORK_ERROR;
        } else {
            long status = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            result.code = static_cast<Spotify::RFC2616_Code>(status);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::remove(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) return result;

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        if (!body.empty()) {
            headers = curl_slist_append(headers, "Content-Type: application/json");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        if (!body.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body.length());
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            result.code = Spotify::RFC2616_Code::NETWORK_ERROR;
        } else {
            long status = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            result.code = static_cast<Spotify::RFC2616_Code>(status);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }
}
