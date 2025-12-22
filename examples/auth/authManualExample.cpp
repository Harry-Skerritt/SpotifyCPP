//
// Created by Harry Skerritt on 18/12/2025.
//

#include <cstdlib>
#include <spotify/spotify.hpp>

int main() {
    std::cout << "Starting " << Spotify::getLibraryName()
  << " v" << Spotify::getLibraryVersion() << std::endl;
    std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
    std::cout << "--------------------------------------------" << "\n" << std::endl;

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
    {Spotify::Scope::UserReadPrivate, Spotify::Scope::UserReadEmail});

    // Display URL
    std::cout << "Please visit the following url: " << url << std::endl;


    // Allow the user to enter the code
    std::cout << "Enter code from url: ";
    std::string code;
    std::getline(std::cin, code);

    // Get the auth token from the code
    if(!code.empty()) {

        if (auth_client.exchangeCode(code)) {
            std::cout << "Authorization successful" << std::endl;
        } else {
            std::cout << "Authorization failed with code: " << Spotify::Tools::stringifyResponse(auth_client.getError()) << std::endl;
            return 1;
        }
    }

    std::cout << "Type anything to refresh token: ";
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return 1;


    if (auth_client.refreshAccessToken()) {
        std::cout << "Re-Authorization successful" << std::endl;
    } else {
        std::cout << "Re-Authorization failed with code: " << Spotify::Tools::stringifyResponse(auth_client.getError()) << std::endl;
        return 1;
    }

    return 0;
}
