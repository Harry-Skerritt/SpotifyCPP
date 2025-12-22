//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef BROWSEAPI_H
#define BROWSEAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class BrowseAPI : public BaseAPI {
    // Funcs
    public:

        explicit BrowseAPI(Client* client) : BaseAPI(client) {};

        // Market
        std::optional<std::vector<std::string>> getAvailableMarkets() const;

        // Search
        std::optional<SearchObject> searchForItem(std::string& q, const std::vector<SearchType>& type,
            const std::optional<std::string>& market = std::nullopt, const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt, const std::optional<std::string>& include_external = std::nullopt) const;


    // Vars
    private:
        const std::string BASE_BROWSE_URL = "https://api.spotify.com/v1/";
    };

}

#endif //BROWSEAPI_H
