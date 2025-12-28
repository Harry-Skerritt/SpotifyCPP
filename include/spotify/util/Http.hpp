//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef HTTP_H
#define HTTP_H

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"


    namespace Spotify::HTTP {
        struct Result {
            Spotify::RFC2616_Code code;
            std::string body;
        };

        using HeaderMap = std::map<std::string, std::string>;


        // for API
        Result get(const std::string& url, const std::string& bearer, const HeaderMap &extra_headers = {});
        Result post(const std::string& url, const std::string& bearer, const std::string& body,const HeaderMap &extra_headers = {});
        Result put (const std::string& url, const std::string& bearer, const std::string& body, const HeaderMap &extra_headers = {});
        Result remove(const std::string& url, const std::string& bearer, const std::string& body,const HeaderMap &extra_headers = {});

    }





#endif //HTTP_H
