//
// Created by Harry Skerritt on 24/12/2025.
//

#ifndef PLAYLISTAPI_H
#define PLAYLISTAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class PlaylistAPI : public BaseAPI {
    // Funcs
    public:

        explicit PlaylistAPI(Client* client) : BaseAPI(client) {}

        // GET
        [[nodiscard]] std::optional<PlaylistObject> getPlaylist(const std::string& playlist_id, const std::optional<std::string>& market = std::nullopt,
            const std::optional<std::string>& fields = std::nullopt,  const std::optional<AdditionalType>& additional_types = std::nullopt) const;
        [[nodiscard]] std::optional<PagedPlaylistTrackObject> getPlaylistItems(const std::string& playlist_id, const std::optional<std::string>& market = std::nullopt,
            const std::optional<std::string>& fields = std::nullopt, const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset = std::nullopt,
            const std::optional<AdditionalType>& additional_types = std::nullopt) const;
        [[nodiscard]] std::optional<PagedPlaylistObject> getCurrentUsersPlaylists(const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset = std::nullopt) const;
        [[nodiscard]] std::optional<PagedPlaylistObject> getUsersPlaylists(const std::string& user_id, const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset = std::nullopt) const;
        [[nodiscard]] std::optional<std::vector<ImageObject>> getPlaylistCoverImage(const std::string& playlist_id) const;

        // PUT
        void changePlaylistDetails(const std::string& playlist_id, const std::optional<std::string>& name = std::nullopt, const std::optional<bool>& is_public = std::nullopt, const std::optional<std::string>& description = std::nullopt,const std::optional<bool>& is_collaborative = std::nullopt) const;
        void replacePlaylistItems(const std::string& playlist_id, const std::vector<std::string>& uris) const;
        void reorderPlaylistItems(const std::string& playlist_id, const int& range_start,const int& insert_before, const std::optional<int>& range_length = std::nullopt, const std::optional<std::string>& snapshot_id = std::nullopt) const;
        void addCustomPlaylistCover(const std::string& playlist_id, const std::string& image) const;

        // POST
        void addItemsToPlaylist(const std::string& playlist_id, const std::vector<std::string>& uris, const std::optional<int>& position = std::nullopt) const;
        std::optional<PlaylistObject> createPlaylist(const std::string& user_id, const std::string& name, const std::optional<bool>& is_public = std::nullopt, const std::optional<bool>& is_collaborative = std::nullopt, const std::optional<std::string>& description = std::nullopt) const;

        // DELETE
        void removePlaylistItems(const std::string& playlist_id, const std::vector<URIObject>& tracks, const std::optional<std::string>& snapshot_id = std::nullopt) const;

    // Vars
    private:
        const std::string BASE_PLAYLIST_URL = "https://api.spotify.com/v1/playlists";
        const std::string BASE_PLAYLIST_USER_URL = "https://api.spotify.com/v1/me/playlists";
        const std::string BASE_USER_URL = "https://api.spotify.com/v1/users";


    };
}

#endif //PLAYLISTAPI_H
