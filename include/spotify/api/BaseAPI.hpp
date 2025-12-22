//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef BASEAPI_HPP
#define BASEAPI_HPP

#endif //BASEAPI_HPP

#pragma once
#include <optional>
#include <string>
#include <iostream>
#include "nlohmann/json.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {
    class Client;

    class BaseAPI {
    protected:
        Client* m_client;
        explicit BaseAPI(Client* client) : m_client(client) {}

        // --- GET + Parse Helper ---
        template <typename T>
        std::optional<T> fetchAndParse(const std::string& url, const std::string& wrapperKey = "") const {
            if (!m_client) return std::nullopt;

            std::string token = tryGetAccessToken();
            auto result = HTTP::get(url, token);

            // Error Handling
            if (result.code != RFC2616_Code::OK && result.code != RFC2616_Code::NO_CONTENT) {
                std::cerr << "API Error [" << (int)result.code << "]: " << result.body << std::endl;
                return std::nullopt;
            }

            if (result.body.empty()) return std::nullopt;

            //std::cout << result.body << std::endl;

            try {
                auto data = nlohmann::json::parse(result.body);

                // Handle wrapper
                if (!wrapperKey.empty() && data.contains(wrapperKey)) {
                    return data.at(wrapperKey).get<T>();
                }

                return data.get<T>();
            } catch (const std::exception& e) {
                std::cerr << "JSON Mapping Error: " << e.what() << std::endl;
                return std::nullopt;
            }
        }

        // --- PUT/DELETE/POST Helper ---
        void sendAction(const std::string& method, const std::string& url, const std::string& body = "") const {
            if (!m_client) return;

            std::string token = tryGetAccessToken();
            HTTP::Result result;

            if (method == "PUT") result = HTTP::put(url, token, body);
            else if (method == "DELETE") result = HTTP::remove(url, token, body);
            else if (method == "POST") result = HTTP::post(url, token, body);

            if (result.code != RFC2616_Code::OK && result.code != RFC2616_Code::NO_CONTENT) {
                std::cerr << method << " Failed [" << (int)result.code << "]: " << result.body << std::endl;
            }
        }

        [[nodiscard]] std::string tryGetAccessToken() const;



    };
}