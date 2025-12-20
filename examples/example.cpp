//
// Created by Harry Skerritt on 18/12/2025.
//

#include <spotify/Auth.hpp>
#include <spotify/Tools.hpp>
#include <cstdlib>

#include "spotify/Tools.hpp"

int main() {

    // Getting client values from .env
    Spotify::Tools::loadEnv("/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env");
    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (!client_key || !client_secret) {
        std::cerr << "Failed to get environment variables" << std::endl;
        return 1;
    }

    // Creating the client
    Spotify::Auth client({client_key, client_secret});

    // Generate the auth url
    auto url = client.getAuthURL(
    "http://127.0.0.1:8888/callback",
    {"user-read-private", "user-read-email"});

    // Display URL
    std::cout << "Please visit the following url: ";
    std::cout << url << std::endl;


    // Allow the user to enter the code
    std::cout << "Enter code from url: ";
    std::string code;
    std::getline(std::cin, code);

    // Get the auth token from the code
    Spotify::AuthResponse response = client.getAuthToken(code);
    if (response.response_code == Spotify::SUCCESS) {
        std::cout << "Authorization successful" << std::endl;
    } else {
        std::cout << "Authorization failed with code: " << Spotify::Tools::stringifyResponse(response.response_code) << std::endl;
    }





    return 0;
}
