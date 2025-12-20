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
        Auth(Client keys );
        ~Auth() = default;

        std::string getAuthURL(
            const std::string &redirectUri,
            const std::vector<std::string> &scopes,
            std::optional<std::string> state = std::nullopt);

        AuthResponse getAuthToken(const std::string &code);

        AuthResponse refreshAuthToken(const std::optional<std::string>& refresh_token = std::nullopt);

        private:
        AuthResponse buildAuthResponse(const std::string& json);
        [[nodiscard]] std::string encodeClientCreds() const;

        // Vars
        public:
        private:
        Client m_keys;
        std::string m_redirectUri;
        std::string m_refresh_token;
    };
}



#endif //AUTH_H
