//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/auth/Auth.hpp>
#include <spotify/util/Tools.hpp>
#include <spotify/auth/AuthServer.h>
#include <cstdlib>

#include "spotify/core/Client.hpp"


int main () {
    // --- ENV ---
    // Getting client values from .env
    std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
    Spotify::Tools::loadEnv(env_path);

    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (client_key == nullptr || client_secret == nullptr) {
        std::cerr << "CRITICAL: Failed to get env variables!" << std::endl;
        return 1;
    }

    // --- Authorising --- //Todo: Minimise this for examples
    // Creating the client
    Spotify::ClientCredentials credentials(client_key, client_secret);
    Spotify::Auth auth_client(credentials);

    // Generate the auth url + open
    auto url = auth_client.createAuthoriseURL(
    "http://127.0.0.1:8888/callback",
    {"user-read-private", "user-read-email", "user-read-currently-playing"});
    Spotify::AuthServer::openBrowser(url);

    // Get the code and pass to the code;
    std::string code = Spotify::AuthServer::waitForCode("127.0.0.1", 8888, "index.html");

    // Get the auth token from the code
    if(!code.empty()) {
        if (!auth_client.exchangeCode(code)) {
            std::cout << "Authorization failed with code: " << Spotify::Tools::stringifyResponse(auth_client.getError()) << std::endl;
            return 1;
        }
    }

    // --- Getting data ---
    Spotify::Client client(auth_client);

    auto pb_opt = client.player().getCurrentlyPlayingTrack();

    if (!pb_opt.has_value()) {
        std::cout << "Nothing is playing (or private session is active)." << std::endl;
        return 0;
    }

    // Access the underlying object
    const auto& pb = *pb_opt;

    if (!pb.is_playing) {
        std::cout << "Playback is currently paused." << std::endl;
        return 0;
    }

    // handle both Track and Episode types
    std::visit([](auto&& arg) {
        if (arg) {
            // Check if the shared_ptr is valid
            std::cout << "Currently playing: " << arg->name;

            // If it's a TrackObject, it has an 'artists' vector
            using T = std::decay_t<decltype(*arg)>;
            if constexpr (std::is_same_v<T, Spotify::TrackObject>) {
                if (!arg->artists.empty()) {
                    std::cout << " by " << arg->artists[0].name;
                }
            }
            // If it's an EpisodeObject, it might have a 'show' name
            else if constexpr (std::is_same_v<T, Spotify::EpisodeObject>) {
                std::cout << " (Podcast Episode)";
            }

            std::cout << std::endl;
        }
    }, pb.item);
    return 0;
}