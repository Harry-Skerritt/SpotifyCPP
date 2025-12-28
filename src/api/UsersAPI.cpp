//
// Created by Harry Skerritt on 28/12/2025.
//
#include <utility>

#include "spotify/api/UsersAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"
#include "spotify/core/Endpoints.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<UserObject> UsersAPI::getCurrentUserProfile() const {
        const std::string url = Endpoints::ME;
        return fetchAndParse<UserObject>(url);
    }

    std::optional<PagedArtistObject> UsersAPI::getUsersTopArtists(
        const std::optional<std::string> &time_range,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {

        std::string url = Endpoints::ME + "/top/artists";

        std::vector<std::string> params;

        if (time_range.has_value() && !time_range->empty()) {
            if (*time_range == "long_term" ||
                *time_range == "medium_term" ||
                *time_range == "short_term")
            {
                params.push_back("time_range=" + WebTools::urlEncode(*time_range));
            } else {
                throw Spotify::LogicException("Time Range is not valid!");
            }
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

        return fetchAndParse<PagedArtistObject>(url);
    }

    std::optional<PagedTrackObject> UsersAPI::getUsersTopTracks(
        const std::optional<std::string> &time_range,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {

        std::string url = Endpoints::ME + "/top/tracks";

        std::vector<std::string> params;

        if (time_range.has_value() && !time_range->empty()) {
            if (*time_range == "long_term" ||
                *time_range == "medium_term" ||
                *time_range == "short_term")
            {
                params.push_back("time_range=" + WebTools::urlEncode(*time_range));
            } else {
                throw Spotify::LogicException("Time Range is not valid!");
            }
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

    std::optional<UserObject> UsersAPI::getUsersProfile(const std::string &user_id) const {

        std::string url = Endpoints::USERS + "/" + user_id;
        return fetchAndParse<UserObject>(url);
    }

    std::optional<PagedArtistObject> UsersAPI::getFollowedArtists(
        const std::string &type,
        const std::optional<std::string> &after,
        const std::optional<int> &limit)
    {
        std::string url = Endpoints::ME + "/following";

        std::vector<std::string> params;

        if (type != "artist")
            throw Spotify::LogicException("Type is not valid! - Must be 'artist'");

        if (after.has_value() && !after->empty()) {
            params.push_back("after=" + WebTools::urlEncode(*after));
        }
        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedArtistObject>(url);
    }

    std::optional<std::vector<bool> > UsersAPI::checkUserFollowsArtists(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);
        std::string url = Endpoints::ME + "/following/contains/?type=artist&ids=" + id_list;
        return fetchAndParse<std::vector<bool>>(url);
    }

    std::optional<std::vector<bool> > UsersAPI::checkUserFollowsUsers(const std::vector<std::string> &ids) {
        std::string id_list = Tools::toCSV(ids, 0, 50);
        std::string url = Endpoints::ME + "/following/contains/?type=user&ids=" + id_list;
        return fetchAndParse<std::vector<bool>>(url);
    }

    std::optional<std::vector<bool> > UsersAPI::checkUserFollowsPlaylist(const std::string &playlist_id, const std::optional<std::string> &id) {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/followers/contains";

        if (id.has_value() && !id->empty()) {
            url += "?ids=" + WebTools::urlEncode(*id);
        }

        return fetchAndParse<std::vector<bool>>(url);
    }

    // --- PUT ---
    void UsersAPI::followPlaylist(const std::string &playlist_id, const std::optional<bool> &is_public) const {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/followers";

        std::string body;
        if (is_public.has_value()) {
            body = nlohmann::json({{"public", *is_public}}).dump();
        }

        (void)sendAction("PUT", url, body);
    }

    void UsersAPI::followArtist(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::ME + "/following?type=artist";

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("PUT", url, j.dump());
    }

    void UsersAPI::followUser(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::ME + "/following?type=user";

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("PUT", url, j.dump());
    }


    // --- DELETE ---
    void UsersAPI::unfollowPlaylist(const std::string &playlist_id) const {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/followers";
        (void)sendAction("DELETE", url, "");
    }

    void UsersAPI::unfollowArtist(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::ME + "/following?type=artist";

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("DELETE", url, j.dump());
    }

    void UsersAPI::unfollowUser(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::ME + "/following?type=user";

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("DELETE", url, j.dump());
    }







}