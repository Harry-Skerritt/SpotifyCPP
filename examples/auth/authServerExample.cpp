//
// Created by Harry Skerritt on 20/12/2025.
//
#include <spotify/Auth.hpp>
#include <spotify/Tools.hpp>
#include <spotify/AuthServer.h>
#include <cstdlib>

int main() {

    // Getting client values from .env
    std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
    Spotify::Tools::loadEnv(env_path);

    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (client_key == nullptr || client_secret == nullptr) {
        std::cerr << "CRITICAL: Failed to get env variables!" << std::endl;
        return 1;
    }

    // Creating the client
    Spotify::ClientCredentials credentials(client_key, client_secret);
    Spotify::Auth auth_client(credentials);

    // Generate the auth url
    auto url = auth_client.createAuthoriseURL(
    "http://127.0.0.1:8888/callback",
    {"user-read-private", "user-read-email"});

    // Open the url in the browser
    Spotify::AuthServer::openBrowser(url);

    // Get the code and pass to the code;
    std::string code = Spotify::AuthServer::waitForCode("127.0.0.1", 8888, "index.html");

    // Get the auth token from the code
    if(!code.empty()) {

        if (auth_client.exchangeCode(code)) {
            std::cout << "Authorization successful" << std::endl;
        } else {
            std::cout << "Authorization failed with code: " << Spotify::Tools::stringifyResponse(response.response_code) << std::endl;
            return 1;
        }
    }

    return 0;
}