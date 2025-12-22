//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef ALBUMAPI_H
#define ALBUMAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class AlbumAPI : public BaseAPI {
    // Funcs
    public:

        explicit AlbumAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<AlbumObject> getAlbum(const std::string &id, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<AlbumListObject> getMultipleAlbums(const std::vector<std::string>& ids, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<PagedTrackObject> getAlbumTracks(const std::string& id, std::optional<std::string> market = std::nullopt,
            std::optional<int> limit  = std::nullopt, std::optional<int> offset = std::nullopt) const;
        [[nodiscard]] std::optional<PagedSavedAlbumObject> getUsersSavedAlbums(std::optional<int> limit = std::nullopt,
            std::optional<int> offset = std::nullopt, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<std::vector<bool>> checkUsersSavedAlbums(std::vector<std::string> ids) const;
        [[nodiscard]] std::optional<PagedAlbumObject> getNewReleases(std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt) const;


        // PUT
        void saveAlbumsForUser(std::vector<std::string> ids) const;

        // DELETE
        void removeUsersSavedAlbums(std::vector<std::string> ids) const;



    // Vars
    private:
        const std::string BASE_ALBUM_URL = "https://api.spotify.com/v1/albums";
        const std::string BASE_ALBUM_USER_URL = "https://api.spotify.com/v1/me/albums";
        const std::string BASE_BROWSE_URL = "https://api.spotify.com/v1/browse";




    };

}

#endif //ALBUMAPI_H
