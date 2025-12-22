#include "spotify/auth/Auth.hpp"
#include "spotify/auth/AuthServer.hpp"
#ifndef EXAMPLE_UTILS_H
#define EXAMPLE_UTILS_H

#include <spotify/spotify.hpp>
#include <iostream>
#include <cstdlib>

namespace Spotify {
    class ExampleUtils {
    public:
        static Auth authenticateFromEnv() {

            std::cout << "Starting " << Spotify::getLibraryName()
              << " v" << Spotify::getLibraryVersion() << std::endl;
            std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
            std::cout << "--------------------------------------------" << "\n" << std::endl;

            // 1. Load Env
            std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
            Tools::loadEnv(env_path);

            const char* key = std::getenv("SPOTIFY_CLIENT_KEY");
            const char* secret = std::getenv("SPOTIFY_CLIENT_SECRET");

            if (!key || !secret) {
                throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
            }

            // 2. Setup Auth
            Auth auth({key, secret});
            
            // 3. Handshake
            auto url = auth.createAuthoriseURL("http://127.0.0.1:8888/callback",
                {
                    Spotify::Scope::UserReadPrivate,
                    Scope::UserReadPlaybackState,
                    Scope::UserReadCurrentlyPlaying,
                    Scope::UserReadRecentlyPlayed,
                    Scope::UserModifyPlaybackState,
                    Scope::UserLibraryRead
                });

            AuthServer::openBrowser(url);
            std::string code = AuthServer::waitForCode("127.0.0.1", 8888, "index.html");

            if (code.empty() || !auth.exchangeCode(code)) {
                throw std::runtime_error("Authorization failed!");
            }

            return auth;
        }
    };
}

#endif