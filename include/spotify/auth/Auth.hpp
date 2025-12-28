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

#include "spotify/util/Tools.hpp"
#include "spotify/util/Types.h"
#include "spotify/util/base64.hpp"
#include "spotify/util/Scopes.hpp"


namespace Spotify {

    class Auth {
        // Funcs
        public:
        explicit Auth(const ClientCredentials& credentials);
        ~Auth() = default;

        // OAuth2 Flow
        std::string createAuthoriseURL(
            const std::string &redirectUri,
            const std::vector<Scope> &scopes,
            const std::optional<std::string>& state = std::nullopt);

        void exchangeCode(const std::string &code);
        void refreshAccessToken(const std::optional<std::string>& refresh_token = std::nullopt);


        // Getters
        std::string getAccessToken();

        private:
        AuthResponse buildAuthResponse(const std::string& json);
        [[nodiscard]] std::string encodeClientCredentials() const;
        bool isTokenExpired() const;


        // Vars
        private:

        const std::string TOKEN_URL = "https://accounts.spotify.com/api/token";
        const std::string AUTH_URL = "https://accounts.spotify.com/authorize";

        ClientCredentials m_credentials;
        std::string m_redirectUri;
        AuthResponse m_authResponse;
        std::string m_refresh_token;

    };
}



#endif //AUTH_H
