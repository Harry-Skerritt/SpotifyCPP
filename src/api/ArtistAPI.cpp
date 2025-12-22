//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/ArtistAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<ArtistObject> ArtistAPI::getArtist(const std::string &id) const {

        std::string url = BASE_ARTIST_URL + "/" + WebTools::urlEncode(id);

        return fetchAndParse<ArtistObject>(url);
    }

    std::optional<ArtistListObject> ArtistAPI::getMultipleArtists(const std::vector<std::string> &ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_ARTIST_URL + "?ids=" + id_list;

       return fetchAndParse<ArtistListObject>(url);
    }

    std::optional<PagedAlbumObject> ArtistAPI::getArtistsAlbums(const std::string &id, std::optional<std::vector<IncludeGroups> > include_groups, std::optional<std::string> market, std::optional<int> limit, std::optional<int> offset) const {

        std::string url = BASE_ARTIST_URL + "/" + WebTools::urlEncode(id) + "/albums";

        std::vector<std::string> params;

        if (include_groups.has_value() && !include_groups->empty() && include_groups->size() <= 4) {
            std::string group_str = buildIncludeGroupsString(*include_groups);
            params.push_back("include_groups=" + WebTools::urlEncode(group_str));
        }

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
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

        return fetchAndParse<PagedAlbumObject>(url);
    }

    std::optional<TrackListObject> ArtistAPI::getArtistTopTracks(const std::string &id, std::optional<std::string> market) const {

        std::string url = BASE_ARTIST_URL + "/" + WebTools::urlEncode(id) + "/top-tracks";

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<TrackListObject>(url);
    }

}
