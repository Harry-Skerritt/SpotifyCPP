//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef SPOTIFYVERSION_HPP
#define SPOTIFYVERSION_HPP

#include <string>

#define SPOTIFY_LIB_NAME "SpotifyAPILib"
#define SPOTIFY_VERSION_MAJOR 0
#define SPOTIFY_VERSION_MINOR 2
#define SPOTIFY_VERSION_PATCH 0

#define SPOTIFY_STR_HELPER(x) #x
#define SPOTIFY_STR(x) SPOTIFY_STR_HELPER(x)

#define SPOTIFY_VERSION_STR \
    SPOTIFY_STR(SPOTIFY_VERSION_MAJOR) "." \
    SPOTIFY_STR(SPOTIFY_VERSION_MINOR) "." \
    SPOTIFY_STR(SPOTIFY_VERSION_PATCH)

namespace Spotify {
    inline std::string getLibraryVersion() {
        return SPOTIFY_VERSION_STR;
    }

    inline std::string getLibraryName() {
        return SPOTIFY_LIB_NAME;
    }
}

#endif //SPOTIFYVERSION_HPP
