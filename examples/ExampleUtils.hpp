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
        static Auth authenticateFromEnv(bool suppress = false) {
            try {
                std::cout << "Starting " << Spotify::getLibraryName()
              << " v" << Spotify::getLibraryVersion() << std::endl;
                std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
                std::cout << "--------------------------------------------" << "\n" << std::endl;

                // Load Env
                std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
                Tools::loadEnv(env_path);

                const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
                const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

                if (!client_key || !client_secret) {
                    throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
                }

                // Setup Auth
                Auth auth({client_key, client_secret});

                // Handshake
                auto url = auth.createAuthoriseURL(
                    "http://127.0.0.1:8888/callback",
                    {
                        Scope::UserReadPrivate,
                        Scope::UserReadPlaybackState,
                        Scope::UserReadCurrentlyPlaying,
                        Scope::UserReadRecentlyPlayed,
                        Scope::UserModifyPlaybackState,
                        Scope::UserLibraryRead,
                        Scope::UserLibraryModify,
                        Scope::UserReadPlaybackPosition,
                        Scope::PlaylistModifyPublic,
                        Scope::PlaylistModifyPrivate,
                        Scope::UGCImageUpload

                    });

                AuthServer::openBrowser(url);
                std::string code = AuthServer::waitForCode("127.0.0.1", 8888, std::nullopt, suppress);
                auth.exchangeCode(code);
                if (!suppress) {
                    std::cout << "Authorization successful!" << std::endl;
                }


                return auth;

            }
            catch (const Spotify::APIException& e) {
                std::cerr << "\n[Spotify API Error] Status: " << e.status()
                          << "\nReason: " << e.reason()
                          << "\nMessage: " << e.message() << std::endl;
            }
            catch (const Spotify::NetworkException& e) {
                std::cerr << "\n[Network Error] " << e.what() << std::endl;
            }
            catch (const Spotify::LogicException& e) {
                std::cerr << "\n[Configuration Error] " << e.what() << std::endl;
            }
            catch (const Spotify::Exception& e) {
                std::cerr << "\n[Library Error] " << e.what() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "\n[Standard Exception] " << e.what() << std::endl;
            }
        }
    };
}

#endif