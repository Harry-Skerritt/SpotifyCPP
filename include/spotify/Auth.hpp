//
// Created by Harry Skerritt on 18/12/2025.
//

#ifndef AUTH_H
#define AUTH_H

#include <random>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <curl/curl.h>

#include "spotify/Tools.hpp"
#include "spotify/Types.h"
#include "spotify/base64.hpp"


namespace Spotify {

    class Auth {
        // Funcs
        public:
        explicit Auth(const ClientCredentials& credentials);
        ~Auth() = default;

        // OAuth2 Flow
        std::string createAuthoriseURL(
            const std::string &redirectUri,
            const std::vector<std::string> &scopes,
            const std::optional<std::string>& state = std::nullopt);

        bool exchangeCode(const std::string &code);
        bool refreshAccessToken(const std::optional<std::string>& refresh_token = std::nullopt);


        // Getters
        std::string getAccessToken();
        [[nodiscard]] AuthResponse getAuthResponse() const;
        [[nodiscard]] ResponseCode getError() const;

        private:
        AuthResponse buildAuthResponse(const std::string& json);
        [[nodiscard]] std::string encodeClientCredentials() const;
        bool isTokenExpired() const;


        // Vars
        public:
        private:
        ClientCredentials m_credentials;
        std::string m_redirectUri;
        AuthResponse m_authResponse;
        std::string m_refresh_token;

    };
}



#endif //AUTH_H
