//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef CATEGORYAPI_H
#define CATEGORYAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class CategoryAPI : public BaseAPI {
        // Funcs
    public:
        explicit CategoryAPI(Client* client) : BaseAPI(client) {}

        // GET
        [[nodiscard]] std::optional<PagedCategoryObject> getMultipleBrowseCategories(const std::optional<std::string> &locale = std::nullopt, std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt) const;
        [[nodiscard]] std::optional<CategoryObject> getBrowseCategory(const std::string& category_id, const std::optional<std::string> &locale = std::nullopt) const;

        // Vars
    private:
         const std::string BASE_CATEGORY_URL = "https://api.spotify.com/v1/browse/categories";
    };
}


#endif //CATEGORYAPI_H
