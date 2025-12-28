//
// Created by Harry Skerritt on 21/12/2025.
//

#include <iostream>
#include <curl/curl.h>

#include "spotify/util/Http.hpp"
#include "spotify/util/base64.hpp"
#include "spotify/core/Errors.hpp"


namespace Spotify {
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    static curl_slist* prepareHeaders(const std::string& bearer, const HTTP::HeaderMap &extra, bool is_auth = false) {
        curl_slist* headers = NULL;

        std::string auth = "Authorization: Bearer " + bearer;
        if (!is_auth) {
            headers = curl_slist_append(headers, auth.c_str());
            headers = curl_slist_append(headers, "User-Agent: spotify-cpp-client");
        }

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

        if (!curl) {
            throw Spotify::Exception("Failed to initialize CURL handle (System error).");
        }

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            std::string err = curl_easy_strerror(code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw Spotify::NetworkException(err);
        }

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        result.code = static_cast<Spotify::RFC2616_Code>(status);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::post(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers, bool is_auth) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) {
            throw Spotify::Exception("Failed to initialize CURL handle (System error).");
        }

        curl_slist *headers = prepareHeaders(bearer, extra_headers, is_auth);

        if (!body.empty() && !extra_headers.contains("Content-Type")) {
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
            std::string err = curl_easy_strerror(code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw Spotify::NetworkException(err);
        }

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        result.code = static_cast<Spotify::RFC2616_Code>(status);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::put(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) {
            throw Spotify::Exception("Failed to initialize CURL handle (System error).");
        }

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        if (!body.empty() && !extra_headers.contains("Content-Type")) {
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
            std::string err = curl_easy_strerror(code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw Spotify::NetworkException(err);
        }

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        result.code = static_cast<Spotify::RFC2616_Code>(status);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    HTTP::Result HTTP::remove(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) {
            throw Spotify::Exception("Failed to initialize CURL handle (System error).");
        }

        curl_slist *headers = prepareHeaders(bearer, extra_headers);

        if (!body.empty() && !extra_headers.contains("Content-Type")) {
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
            std::string err = curl_easy_strerror(code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw Spotify::NetworkException(err);
        }

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        result.code = static_cast<Spotify::RFC2616_Code>(status);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return result;
    }

    // Other
    HTTP::Result HTTP::getImage(const std::string &url) {
        CURL *curl;
        HTTP:Result result { Spotify::RFC2616_Code::NOT_IMPLEMENTED, "" };

        curl = curl_easy_init();

        if (!curl) {
            throw Spotify::Exception("Failed to initialize CURL handle (System error).");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);

        auto code = curl_easy_perform(curl);

        if (code != CURLE_OK) {
            std::string err = curl_easy_strerror(code);
            curl_easy_cleanup(curl);
            throw Spotify::NetworkException(err);
        }

        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        result.code = static_cast<Spotify::RFC2616_Code>(status);

        curl_easy_cleanup(curl);
        return result;
    }

}
