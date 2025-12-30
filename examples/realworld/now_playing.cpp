//
// Created by Harry Skerritt on 30/12/2025.
//

#include <spotify/spotify.hpp>

#include <chrono>
#include <string>
#include <thread>

using namespace Spotify;

// Example CLI Spotify Player
// Shows how to authenticate, retrieve the currently playing track,
// and display playback info in a loop with live updates.


// This function renders the processed data to the console
void renderPlayback(const std::optional<PlaybackObject>& playback_state, const std::optional<PlaybackObject>& current_track) {
    // Process the information retrieved from the API and display it

    // Clear screen and move cursor to top (ANSI escape codes)
    std::cout << "\033[2J\033[H";

    // Output a header to make it clear what is being displayed
    std::cout << "────────────────────────────────────────" << std::endl;
    std::cout << "🎵 Now Playing                          " << std::endl;
    std::cout << "────────────────────────────────────────\n" << std::endl;

    // Handle no track being played
    if (!current_track.has_value() || !playback_state.has_value()) {
        std::cout << "Nothing is currently playing!" << std::endl;
        return;
    }

    // Note: Only handling music tracks here; for podcasts or audiobooks, use current_track->asEpisode()
    // Check if the currently playing item is a track (music)
    if (current_track->asTrack() != nullptr) {
        // Parse data out of object and display to the console
        const auto track = current_track->asTrack();
        std::cout << "Track  : " << track->name << std::endl;
        std::cout << "Artist : " << (track->artists.empty() ? "Unknown" : track->artists.at(0).name) << std::endl;
        std::cout << "Album  : " << track->album.name << std::endl;
        std::cout << "Time   : " << Tools::formatMs(current_track->progress_ms) << " / "  << Tools::formatMs(track->duration_ms) << std::endl;
    }
    if (playback_state->asTrack()) {
        std::cout << "\nDevice : " << playback_state->device.name << std::endl;
        std::cout << "Status : " << (playback_state->is_playing ? "▶ Playing" : "⏹ Not Playing") << std::endl;
    }

    std::cout << "\n────────────────────────────────────────" << std::endl;
    std::cout << "(Press Ctrl+C to quit)" << std::endl; // Quits the infinte loop in main()
}

int main () {
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
                Scope::UserReadPlaybackState,
                Scope::UserReadCurrentlyPlaying
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

        // Create a client
        Client client(auth);

        // Loop until user quits (Ctrl+C)
        while (true) {
            // Poll the API at the target end point
            auto current_track = client.player().getCurrentlyPlayingTrack();
            auto playback_state = client.player().getPlaybackState();

            // Send the retrieved data to the render function
            renderPlayback(playback_state, current_track);

            // Poll every 2 seconds
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
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
}