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

#include <spotify/Tools.hpp>


namespace Spotify {

    enum ResponseCode {
        SUCCESS,
        NETWORK_ERROR,
        AUTH_ERROR,
        PARSE_ERROR
    };

    struct ClientKeys {
        std::string client_id;
        std::string client_secret;
    };

    struct AuthResponse {
        std::string access_token;
        std::string token_type;
        std::string scope;
        int expires_in = 0;
        std::string refresh_token;
        ResponseCode response_code;
    };

    class Auth {
        // Funcs
        public:
        Auth(ClientKeys keys );
        ~Auth() = default; // Todo: for now

        std::string getAuthURL(
            const std::string &redirectUri,
            const std::vector<std::string> &scopes,
            std::optional<std::string> state = std::nullopt);

        AuthResponse getAuthToken(const std::string &code);

        private:


        // Vars
        public:
        private:
        ClientKeys m_keys;
        std::string m_redirectUri;
    };
}



#endif //AUTH_H
