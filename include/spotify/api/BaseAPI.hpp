//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef BASEAPI_HPP
#define BASEAPI_HPP

#pragma once
#include <optional>
#include <string>
#include <iostream>

#include "spotify/core/Errors.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"
#include "spotify/util/JsonMapping.hpp"

#include "nlohmann/json.hpp"

namespace Spotify {
    class Client;

    class BaseAPI {
    protected:
        Client* m_client;
        explicit BaseAPI(Client* client) : m_client(client) {}



        // --- GET + Parse Helper ---
        template <typename T>
        T fetchAndParse(const std::string& url, const std::string& wrapperKey = "") const {
            auto result = fetchAndParseOptional<T>(url, wrapperKey);
            if (!result.has_value()) {
                throw Spotify::ParseException("API returned 204 No Content or empty body where data was expected.", "");
            }
            return *result;
        }

        template <typename T>
        std::optional<T> fetchAndParseOptional(const std::string& url, const std::string& wrapperKey = "") const {
            if (!m_client) throw std::runtime_error("SpotifyAPI: Attempted to fetch data without an initialized HTTP client.");

            std::string token = tryGetAccessToken();
            auto result = HTTP::get(url, token);

            if (result.code == RFC2616_Code::NO_CONTENT || (result.code == RFC2616_Code::OK && result.body.empty())) {
                return std::nullopt;
            }

            // Error Handling
            ErrorHandler::verifyResponse(result);

            try {
                auto data = nlohmann::json::parse(result.body);

                // Handle wrapper
                if (!wrapperKey.empty() && data.contains(wrapperKey)) {
                    return data.at(wrapperKey).get<T>();
                }

                return data.get<T>();
            } catch (const std::exception& e) {
                std::string error_msg = "Failed to parse Spotify response. JSON Error: " + std::string(e.what());
                throw Spotify::ParseException(error_msg, result.body);
            }
        }

        // --- PUT/DELETE/POST Helper ---
        [[nodiscard]] std::optional<std::string> sendAction(const std::string& method, const std::string& url, const std::string& body = "", const HTTP::HeaderMap& extra_headers = {}) const {
            if (!m_client) return std::nullopt;

            std::string token = tryGetAccessToken();
            HTTP::Result result = {};

            if (method == "GET") result = HTTP::get(url, token);
            else if (method == "PUT") result = HTTP::put(url, token, body, extra_headers);
            else if (method == "DELETE") result = HTTP::remove(url, token, body, extra_headers);
            else if (method == "POST") result = HTTP::post(url, token, body, extra_headers);
            else {
               throw std::invalid_argument("Unsupported HTTP method: " + method);
            }

            ErrorHandler::verifyResponse(result);

            return result.body;
        }

        [[nodiscard]] std::string tryGetAccessToken() const;



    };
}
#endif //BASEAPI_HPP