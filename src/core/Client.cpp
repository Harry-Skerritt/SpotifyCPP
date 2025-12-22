//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/core/Client.hpp"

#include "spotify/api/AlbumAPI.hpp"
#include "spotify/api/ArtistAPI.hpp"
#include "spotify/api/AudiobookAPI.hpp"
#include "spotify/api/BrowseAPI.h"
#include "spotify/api/CategoryAPI.hpp"
#include "spotify/api/ChapterAPI.hpp"
#include "spotify/api/EpisodeAPI.hpp"
#include "spotify/api/PlayerAPI.hpp"


namespace Spotify {
    Client::Client(Auth& auth) : m_auth(auth) { }

    std::string Client::getAccessToken() const {
        return m_auth.getAccessToken();
    }

    // APIs
    AlbumAPI Client::album() {
        return AlbumAPI(this);
    }

    ArtistAPI Client::artist() {
        return ArtistAPI(this);
    }

    AudiobookAPI Client::audiobook() {
        return AudiobookAPI(this);
    }

    BrowseAPI Client::browse() {
        return BrowseAPI(this);
    }

    CategoryAPI Client::category() {
        return CategoryAPI(this);
    }

    ChapterAPI Client::chapter() {
        return ChapterAPI(this);
    }

    EpisodeAPI Client::episode() {
        return EpisodeAPI(this);
    }

    PlayerAPI Client::player() {
        return PlayerAPI(this);
    }
}




