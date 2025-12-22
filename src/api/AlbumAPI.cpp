//
// Created by Harry Skerritt on 21/12/2025.
//

#include <utility>

#include "spotify/api/AlbumAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<AlbumObject> AlbumAPI::getAlbum(const std::string &id, std::optional<std::string> market) const {

        std::string url = BASE_ALBUM_URL + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<AlbumObject>(url);
    }

    std::optional<AlbumListObject> AlbumAPI::getMultipleAlbums(const std::vector<std::string>& ids, std::optional<std::string> market) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);

        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_ALBUM_URL + "?ids=" + id_list;

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<AlbumListObject>(url);
    }

    std::optional<PagedTrackObject> AlbumAPI::getAlbumTracks(const std::string &id, std::optional<std::string> market, std::optional<int> limit, std::optional<int> offset) const {

        std::string url = BASE_ALBUM_URL + "/" + WebTools::urlEncode(id) + "/tracks";

        std::vector<std::string> params;

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

        return fetchAndParse<PagedTrackObject>(url);
    }

    std::optional<PagedSavedAlbumObject> AlbumAPI::getUsersSavedAlbums(std::optional<int> limit, std::optional<int> offset, std::optional<std::string> market) const {

        std::string url = BASE_ALBUM_USER_URL;

        std::vector<std::string> params;

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

        return fetchAndParse<PagedSavedAlbumObject>(url);
    }

    std::optional<std::vector<bool> > AlbumAPI::checkUsersSavedAlbums(std::vector<std::string> ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_ALBUM_URL + "/contains?ids=" + id_list;

        return fetchAndParse<std::vector<bool>>(url);
    }

    std::optional<PagedAlbumObject> AlbumAPI::getNewReleases(std::optional<int> limit, std::optional<int> offset) const {
        std::string url = BASE_BROWSE_URL + "/new-releases";

        std::vector<std::string> params;

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

        return fetchAndParse<PagedAlbumObject>(url, "albums");
    }


    // --- PUT ---
    void AlbumAPI::saveAlbumsForUser(std::vector<std::string> ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return;
        }

        std::string url = BASE_ALBUM_USER_URL + "?ids=" + id_list;

        sendAction("PUT", url);
    }


    // --- DELETE ---
    void AlbumAPI::removeUsersSavedAlbums(std::vector<std::string> ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return;
        }

        std::string url = BASE_ALBUM_USER_URL + "?ids=" + id_list;

        nlohmann::json j;
        j["ids"] = id_list;

        sendAction("DELETE", url, j.dump());
    }



}
