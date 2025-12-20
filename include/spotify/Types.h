//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TYPES_H
#define TYPES_H

#include <map>

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

    inline std::map<int, std::string> RFC2616_Table =
    {
        {200, "OK"},
        {201, "Created"},
        {202, "Accepted"},
        {204, "No Content"},
        {304, "Not Modified"},
        {400, "Bad Request"},
        {401, "Unauthorized"},
        {403, "Forbidden"},
        {404, "Not Found"},
        {429, "Too Many Requests"},
        {500, "Internal Server Error"},
        {502, "Bad Gateway"},
        {503, "Service Unavailable"}
    };
}

#endif //TYPES_H
