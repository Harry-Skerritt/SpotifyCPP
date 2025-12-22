//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#pragma once
#include <string>
#include "spotify/auth/Auth.hpp"


namespace Spotify {

    class AlbumAPI;
    class ArtistAPI;
    class AudiobookAPI;
    class CategoryAPI;
    class ChapterAPI;
    class PlayerAPI;

    class Client {
    // Funcs
    public:
        explicit Client(Auth& auth);
        ~Client() = default;

        [[nodiscard]] std::string getAccessToken() const;

        AlbumAPI album();
        ArtistAPI artist();
        AudiobookAPI audiobook();
        CategoryAPI category();
        ChapterAPI chapter();
        PlayerAPI player();





    private:

    // Vars
    public:
        const std::string BASE_API_URL = "https://api.spotify.com/v1/";

    private:
        Auth& m_auth;

    };

}



#endif //CLIENT_H
