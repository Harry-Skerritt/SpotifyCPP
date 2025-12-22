//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef ARTISTAPI_HPP
#define ARTISTAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ArtistAPI : public BaseAPI {
    // Funcs
    public:

        explicit ArtistAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<ArtistObject> getArtist(const std::string &id) const;
        [[nodiscard]] std::optional<ArtistListObject> getMultipleArtists(const std::vector<std::string>& ids) const;
        [[nodiscard]] std::optional<PagedAlbumObject> getArtistsAlbums(const std::string &id,
            std::optional<std::vector<IncludeGroups>> include_groups = std::nullopt,
            std::optional<std::string> market = std::nullopt,
            std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt) const;
        [[nodiscard]] std::optional<TrackListObject> getArtistTopTracks(const std::string &id, std::optional<std::string> market = std::nullopt) const;

    // Vars
    private:
        const std::string BASE_ARTIST_URL = "https://api.spotify.com/v1/artists";
    };
}

#endif //ARTISTAPI_HPP
