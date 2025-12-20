//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TYPES_H
#define TYPES_H

namespace Spotify {
    struct Client {
        std::string client_id;
        std::string client_secret;
    };

    enum ResponseCode {
        SUCCESS,
        NETWORK_ERROR,
        AUTH_ERROR,
        PARSE_ERROR,
        VALUE_ERROR
    };

    struct AuthResponse {
        std::string access_token;
        std::string token_type;
        std::string scope;
        int expires_in = 0;
        std::string refresh_token;
        ResponseCode response_code;
    };
}

#endif //TYPES_H
