//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#pragma once
#include <string>

#include "spotify/api/EpisodeAPI.hpp"
#include "spotify/auth/Auth.hpp"


namespace Spotify {

    class AlbumAPI;
    class ArtistAPI;
    class AudiobookAPI;
    class BrowseAPI;
    class CategoryAPI;
    class ChapterAPI;
    class EpisodeAPI;
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
        BrowseAPI browse();
        CategoryAPI category();
        ChapterAPI chapter();
        EpisodeAPI episode();
        PlayerAPI player();


    // Vars
    private:
        Auth& m_auth;

    };

}



#endif //CLIENT_H
