//
// Created by Harry Skerritt on 22/12/2025.
//
#pragma once

#include <utility>
#include "spotify/api/BrowseAPI.h"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- Market ---
    std::optional<std::vector<std::string>> BrowseAPI::getAvailableMarkets() const {
        std::string url = BASE_BROWSE_URL + "markets";

        return fetchAndParse<std::vector<std::string>>(url, "markets");
    }


    // --- Search ---
    std::optional<SearchObject> BrowseAPI::searchForItem(std::string &q, const std::vector<SearchType> &type, const std::optional<std::string> &market, const std::optional<int> &limit, const std::optional<int> &offset, const std::optional<std::string> &include_external) const {

        std::string url = BASE_BROWSE_URL + "search?q=" + WebTools::urlEncode(q);

        std::string type_str = buildSearchTypeString(type);
        url += "&type=" + WebTools::urlEncode(type_str);

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            url += "&market=" + WebTools::urlEncode(*market);
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            url += "&limit=" + std::to_string(*limit);
        }

        if (offset && offset >= 0) {
            url += "&offset=" + std::to_string(*offset);
        }

        return fetchAndParse<SearchObject>(url);


    }


}
