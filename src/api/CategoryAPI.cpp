//
// Created by Harry Skerritt on 22/12/2025.
//
#include "spotify/api/CategoryAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"


namespace Spotify {

    // --- GET ---
    std::optional<CategoryObject> CategoryAPI::getBrowseCategory(const std::string& category_id, const std::optional<std::string> &locale) const {

        std::string url = BASE_CATEGORY_URL + "/" + WebTools::urlEncode(category_id);

        if (locale.has_value() && !locale->empty()) {
            url += "?locale=" +  WebTools::urlEncode(*locale);
        }

        return fetchAndParse<CategoryObject>(url);

    }

    std::optional<PagedCategoryObject> CategoryAPI::getMultipleBrowseCategories(const std::optional<std::string> &locale, const std::optional<int> limit, const std::optional<int> offset) const {

        std::string url = BASE_CATEGORY_URL;

        std::vector<std::string> params;

        if (locale.has_value() && !locale->empty()) {
            params.push_back("locale=" + WebTools::urlEncode(*locale));
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedCategoryObject>(url, "categories");
    }



}