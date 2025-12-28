//
// Created by Harry Skerritt on 24/12/2025.
//

#include <utility>

#include "spotify/api/PlaylistAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<PlaylistObject> PlaylistAPI::getPlaylist(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string> &fields,
        const std::optional<AdditionalType> &additional_types) const
    {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id;

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + WebTools::urlEncode(*fields));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + WebTools::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PlaylistObject>(url);
    }

    std::optional<PagedPlaylistTrackObject> PlaylistAPI::getPlaylistItems(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string>& fields,
        const std::optional<int> &limit,
        const std::optional<int> &offset,
        const std::optional<AdditionalType>& additional_types) const
    {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + WebTools::urlEncode(*fields));
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + WebTools::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedPlaylistTrackObject>(url);
    }

    std::optional<PagedPlaylistObject> PlaylistAPI::getCurrentUsersPlaylists(
        const std::optional<int> &limit,
        const std::optional<int> &offset) const {

        std::string url = BASE_PLAYLIST_USER_URL;

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

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    std::optional<PagedPlaylistObject> PlaylistAPI::getUsersPlaylists(
        const std::string &user_id,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const {

        std::string url = BASE_USER_URL + "/" + user_id + "/playlists";

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

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    std::optional<std::vector<ImageObject> > PlaylistAPI::getPlaylistCoverImage(const std::string &playlist_id) const {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/images";

        return fetchAndParse<std::vector<ImageObject> >(url);
    }



    // --- PUT ---
    void PlaylistAPI::changePlaylistDetails(
        const std::string &playlist_id,
        const std::optional<std::string> &name,
        const std::optional<bool> &is_public,
        const std::optional<std::string> &description,
        const std::optional<bool> &is_collaborative) const
    {
        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id;


        nlohmann::json j;

        if (name.has_value())
            j["name"] = *name;

        if (is_public.has_value())
            j["public"] = *is_public;

        if (description.has_value())
            j["description"] = *description;

        if (is_collaborative.has_value())
            j["collaborative"] = *is_collaborative;

        sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::replacePlaylistItems(
        const std::string &playlist_id,
        const std::vector<std::string> &uris) const {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        std::string uri_list = Tools::toCSV(uris, 1, 100);
        if (uri_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 100 URIs" << std::endl;
            return;
        }

        nlohmann::json j;
        j["uris"] = uri_list;

        sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::reorderPlaylistItems(
        const std::string& playlist_id,
        const int &range_start,
        const int &insert_before,
        const std::optional<int> &range_length,
        const std::optional<std::string> &snapshot_id) const {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        nlohmann::json j;

        j["range_start"] = range_start;
        j["insert_before"] = insert_before;

        if (range_length.has_value())
            j["range_length"] = *range_length;

        if (snapshot_id.has_value())
            j["snapshot_id"] = *snapshot_id;


        sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::addCustomPlaylistCover(
        const std::string &playlist_id,
        const std::string &image) const
    {
        // Todo:
        // Needs to take in an image and override headers
        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/images";

        nlohmann::json j;
        j["image"] = base64_encode(image);
        sendAction("PUT", url, j.dump());
    }



    // --- POST ---
    void PlaylistAPI::addItemsToPlaylist(
        const std::string &playlist_id,
        const std::vector<std::string> &uris,
        const std::optional<int> &position) const {
        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        if (uris.size() > 100 || uris.size() < 1) {
            std::cerr << "Error: You must provide between 1 and 100 URIs" << std::endl;
            return;
        }

        nlohmann::json j;

        nlohmann::json uri_array = nlohmann::json::array();
        for (const auto &uri : uris) {
            uri_array.push_back(uri );
        }

        j["uris"] = uri_array;

        if (position.has_value())
            j["position"] = *position;

        std::cout << j.dump() << std::endl;

        auto body = sendAction("POST", url, j.dump());
        if (body.has_value()) {
            std::cout << body.value() << std::endl;
        }
    }


    std::optional<PlaylistObject> PlaylistAPI::createPlaylist(
        const std::string &user_id,
        const std::string &name,
        const std::optional<bool> &is_public,
        const std::optional<bool> &is_collaborative,
        const std::optional<std::string> &description) const
    {
        std::string url = BASE_USER_URL + "/" + user_id + "/playlists";

        nlohmann::json j;
        j["name"] = name;

        if (is_public.has_value())
            j["public"] = *is_public;

        if (is_collaborative.has_value())
            j["collaborative"] = *is_collaborative;

        if (description.has_value() && !description->empty())
            j["description"] = *description;

        auto body = sendAction("POST", url, j.dump());

        if (body.has_value()) {
            try {
                auto data = nlohmann::json::parse(*body);

                return data.get<PlaylistObject>();
            } catch (const std::exception& e) {
                std::cerr << "JSON Mapping Error: " << e.what() << std::endl;
                return std::nullopt;
            }
        }

        return std::nullopt;
    }



    // --- DELETE ---
    void PlaylistAPI::removePlaylistItems(
        const std::string &playlist_id,
        const std::vector<URIObject> &tracks,
        const std::optional<std::string> &snapshot_id) const
    {
        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        nlohmann::json j;

        nlohmann::json track_array = nlohmann::json::array();
        for (const auto &track : tracks) {
            track_array.push_back({ {"uri", track.uri} });
        }
        j["tracks"] = track_array;

        if (snapshot_id.has_value() && !snapshot_id->empty())
            j["snapshot_id"] = *snapshot_id;

        sendAction("DELETE", url, j.dump());
    }








}