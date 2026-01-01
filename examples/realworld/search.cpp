//
// Created by Harry Skerritt on 01/01/2026.
//

#include <spotify/spotify.hpp>

using namespace Spotify;

// Render the results
void renderResults(const SearchObject& results) {

    // If artists come back then show them line by line
    if (!results.artists->items.empty()) {
        std::cout << "\nArtists:\n";
        for (std::size_t i = 0; i < results.artists->items.size(); ++i) {
            std::cout << i + 1 << ". "
                      << results.artists->items[i].name
                      << '\n';
        }
    }

    // If albums come back then show them line by line
    if (!results.albums->items.empty()) {
        std::cout << "\nAlbums:\n";
        for (std::size_t i = 0; i < results.albums->items.size(); ++i) {
            std::cout << i + 1 << ". "
                      << results.albums->items[i].name
                      << " - "
                      << results.albums->items[i].artists[0].name
                      << '\n';
        }
    }

    // If tracks come back then show them line by line
    if (!results.tracks->items.empty()) {
        std::cout << "\nTracks:\n";
        for (std::size_t i = 0; i < results.tracks->items.size(); ++i) {
            std::cout << i + 1 << ". "
                      << results.tracks->items[i].name
                      << " - "
                      << results.tracks->items[i].artists[0].name
                      << '\n';
        }
    }
}

int main() {
    std::cout << "Starting " << getLibraryName()
             << " v" << getLibraryVersion() << std::endl;
    std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
    std::cout << "--------------------------------------------" << "\n" << std::endl;

    bool suppress = true; // Suppress console output during auth flow (optional)

    try {
        // Load Client Key and Secret from .env file
        // Either replace the path below with a path to your .env or hardcode the values to client_key and client_secret
        // Note: Make sure to keep your keys safe!
        std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
        Tools::loadEnv(env_path);

        const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
        const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

        // Handle keys being absent
        if (!client_key || !client_secret) {
            throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
        }

        // Create the authentication object
        Auth auth( {client_key, client_secret} );

        // Generate the authorisation url - Replace the redirectUri with the one for your spotify app
        auto url = auth.createAuthoriseURL(
            "http://127.0.0.1:8888/callback",
            {
                Scope::UserTopRead,
                Scope::UserReadPrivate,
                Scope::UserReadEmail
            });


        // Open the URL and authenticate
        AuthServer::openBrowser(url);

        // Automatically handle the code coming in to the redirectURI
        std::string code = AuthServer::waitForCode(
            "127.0.0.1", 8888, std::nullopt, suppress);

        // Exchange the code for an authentication token
        auth.exchangeCode(code);

        // Show success message is enabled
        if (!suppress) {
            std::cout << "Authorization successful!" << std::endl;
        }

        // ************************************************************
        // *  Everything is successfully authenticated at this point  *
        // ************************************************************
        Client client(auth);

        // Get the users search term into a string we can use
        std::cout << "What would you like to search for? ";
        std::string search_term;
        std::getline(std::cin, search_term);

        // Define the item types we are looking for:
        // Artists | Album | Audiobook | Episode | Playlist | Show | Track
        const std::vector<SearchType> search_types = {
            SearchType::Artist,
            SearchType::Album,
            SearchType::Track,
        };

        // Search for the input term, against the search terms within
        // the GB market and return the top 10 items
        auto search_response = client.browse().searchForItem(
            search_term, search_types, "GB", 10);

        renderResults(search_response);
    }
    // Catch any errors and display them in the console
    catch (const APIException& e) {
        std::cerr << "\n[Spotify API Error] Status: " << e.status()
                  << "\nReason: " << e.reason()
                  << "\nMessage: " << e.message() << std::endl;
        throw;
    }
    catch (const NetworkException& e) {
        std::cerr << "\n[Network Error] " << e.what() << std::endl;
        throw;
    }
    catch (const LogicException& e) {
        std::cerr << "\n[Configuration Error] " << e.what() << std::endl;
        throw;
    }
    catch (const Exception& e) {
        std::cerr << "\n[Library Error] " << e.what() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[Standard Exception] " << e.what() << std::endl;
        throw;
    }
    return 0;
}