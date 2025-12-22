//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef EPISODEAPI_HPP
#define EPISODEAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class EpisodeAPI : public BaseAPI {
    // Funcs
    public:

        explicit EpisodeAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<EpisodeObject> getEpisode(const std::string &id, const std::optional<std::string> &market = std::nullopt) const;
        [[nodiscard]] std::optional<EpisodeListObject> getMultipleEpisodes(const std::vector<std::string>& ids, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<PagedEpisodeObject> getUsersSavedEpisodes(const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset = std::nullopt) const;
        [[nodiscard]] std::optional<std::vector<bool>> checkUsersSavedEpisodes(const std::vector<std::string>& ids) const;

        // PUT
        void saveEpisodeForUser(std::vector<std::string>& ids) const;

        // Delete
        void removeUserSavedEpisodes(std::vector<std::string>& ids) const;

    // Vars
    private:
        const std::string BASE_EPISODE_URL = "https://api.spotify.com/v1/episodes";
        const std::string BASE_EPISODE_USER_URL = "https://api.spotify.com/v1/me/episodes";

    };
}

#endif //EPISODEAPI_HPP
