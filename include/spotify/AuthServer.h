//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace Spotify {
    class AuthServer {
        public:
        static std::string waitForCode(const std::string &auth_url, int port = 8888, const std::optional<std::filesystem::path> &html_file_path = std::nullopt);
        static void openBrowser(const std::string& url);

    };
}

#endif //AUTHSERVER_H
