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

    try {
        // Getting client values from .env
        std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
        Spotify::Tools::loadEnv(env_path);

        const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
        const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

        if (!client_key || !client_secret) {
            throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
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
        if(code.empty()) {
            throw Spotify::LogicException("Authorization code cannot be empty.");
        }

        auth_client.exchangeCode(code);
        std::cout << "Authorization successful!" << std::endl;


        // Refresh Test
        std::cout << "Type anything to refresh token: ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty()) {
            auth_client.refreshAccessToken();
            std::cout << "Re-Authorization successful!" << std::endl;
        }

    }
    catch (const Spotify::APIException& e) {
        std::cerr << "\n[Spotify API Error] Status: " << e.status()
                  << "\nReason: " << e.reason()
                  << "\nMessage: " << e.message() << std::endl;
        return 1;
    }
    catch (const Spotify::NetworkException& e) {
        std::cerr << "\n[Network Error] " << e.what() << std::endl;
        return 1;
    }
    catch (const Spotify::ParseException& e) {
        std::cerr << "\n[Parse Error] " << e.what() << std::endl;
        // e.getRawBody() is available if you need to inspect the bad JSON
        return 1;
    }
    catch (const Spotify::LogicException& e) {
        std::cerr << "\n[Logic Error] " << e.what() << std::endl;
        return 1;
    }
    catch (const Spotify::Exception& e) {
        std::cerr << "\n[Library Error] " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[System Error] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
