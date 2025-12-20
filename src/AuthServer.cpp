//
// Created by Harry Skerritt on 20/12/2025.
//

#include "httplib.h"

#include "spotify/AuthServer.h"


void Spotify::AuthServer::openBrowser(const std::string &url) {
#if defined(_WIN32)
    std::string command = "start " + url;
#elif defined(__APPLE__)
    std::string command = "open \"" + url + "\"";
#else
    std::string command = "xdg-open \"" + url + "\"";
#endif
    std::system(command.c_str());
}

std::string Spotify::AuthServer::waitForCode(const std::string &auth_url, int port, const std::optional<std::filesystem::path> &html_file_path) {
    httplib::Server server;
    std::string captured_code;

    std::string response_html = "<html><body style='font-family:sans-serif; text-align:center; padding-top:50px;'>"
                            "<h1>Authenticated!</h1><p>You can close this tab and return to the app.</p>"
                            "</body></html>";

    if (html_file_path.has_value()) {
        std::ifstream file(html_file_path.value());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            response_html = buffer.str();
        }
    }

    // Setup server
    server.Get("/callback", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("code")) {
            captured_code = req.get_param_value("code");
            res.set_content(response_html, "text/html");
            server.stop();
        }
    });

    std::cout << "Waiting for response on " << auth_url << ":" << port << "..." << std::endl;
    server.listen(auth_url, port);

    return captured_code;
}

