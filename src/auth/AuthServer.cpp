//
// Created by Harry Skerritt on 20/12/2025.
//

#include "httplib.h"

#include "spotify/auth/AuthServer.hpp"

#include "spotify/core/Errors.hpp"

namespace Spotify {
    void AuthServer::openBrowser(const std::string &url) {
#if defined(_WIN32)
        std::string command = "start " + url;
#elif defined(__APPLE__)
        std::string command = "open \"" + url + "\"";
#else
        std::string command = "xdg-open \"" + url + "\"";
#endif
        int result = std::system(command.c_str());
        if (result != 0) {
            throw Spotify::Exception("AuthServer: Failed to execute browser open command");
        }
    }

    std::string AuthServer::waitForCode(
        const std::string &auth_url,
        int port,
        const std::optional<std::filesystem::path> &html_file_path,
        bool suppress)
    {
        httplib::Server server;
        std::string captured_code;

        std::string response_html = "<html><body style='font-family:sans-serif; text-align:center; padding-top:50px;'>"
                                "<h1>Authenticated!</h1><p>You can close this tab and return to the app.</p>"
                                "</body></html>";

        if (html_file_path.has_value()) {
            std::ifstream file(html_file_path.value());
            if (!file.is_open()) {
                std::string error_msg = "AuthServer: Failed to open custom HTML file at " + html_file_path.value().string();
                throw Spotify::LogicException(error_msg);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            response_html = buffer.str();
        }

        // Setup server
        server.Get("/callback", [&](const httplib::Request& req, httplib::Response& res) {
            if (req.has_param("code")) {
                captured_code = req.get_param_value("code");
                res.set_content(response_html, "text/html");
                server.stop();
            }
        });

        if (!suppress)
            std::cout << "Waiting for response on " << auth_url << ":" << port << "..." << std::endl;

        if (!server.listen(auth_url, port)) {
            throw Spotify::NetworkException("AuthServer failed to bind to port " + std::to_string(port) +
                                      ". Is the port already in use?");
        }

        if (captured_code.empty()) {
            throw Spotify::Exception("AuthServer: Server stopped without capturing an authorization code.");
        }
        return captured_code;
    }
}


