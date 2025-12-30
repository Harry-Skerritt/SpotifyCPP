//
// Created by Harry Skerritt on 21/12/2025.
//

#include <utility>

#include "spotify/api/PlayerAPI.hpp"
#include "spotify/core/Endpoints.hpp"

#include "nlohmann/json.hpp"


namespace Spotify {

    // --- GET ---
    std::optional<PlaybackObject> PlayerAPI::getPlaybackState(
        const std::optional<std::string> &market,
        const std::optional<std::string> &additional_types ) const
    {
        std::string url = Endpoints::PLAYER;

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (additional_types.has_value()
            && (additional_types == "track" || additional_types == "episode"))
        {
            params.push_back("additional_types=" + WebTools::urlEncode(*additional_types));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }


        return fetchAndParseOptional<PlaybackObject>(url);
    }

    DeviceListObject PlayerAPI::getAvailableDevices() const {

        std::string url = Endpoints::PLAYER + "/devices";

        return fetchAndParse<DeviceListObject>(url);
    }

    std::optional<PlaybackObject> PlayerAPI::getCurrentlyPlayingTrack(
        const std::optional<std::string> &market,
        const std::optional<std::string> &additional_types) const
    {
        std::string url = Endpoints::PLAYER + "/currently-playing";

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (additional_types.has_value()
            && (additional_types == "track" || additional_types == "episode"))
        {
            params.push_back("additional_types=" + WebTools::urlEncode(*additional_types));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }


        return fetchAndParseOptional<PlaybackObject>(url);
    }

    RecentlyPlayedTracksObject PlayerAPI::getRecentlyPlayedTracks(
        const std::optional<int>& limit,
        const std::optional<int64_t>& after,
        const std::optional<int64_t>& before) const
    {
        std::string url = Endpoints::PLAYER + "/recently-played";

        std::vector<std::string> params;

        if (limit.has_value() && Tools::inRange(*limit, 0, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (after.has_value())
        {
            params.push_back("after=" + std::to_string(*after));
        }

        if (before.has_value())
        {
            params.push_back("before=" + std::to_string(*before));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }


        return fetchAndParse<RecentlyPlayedTracksObject>(url);
    }

    QueueObject PlayerAPI::getUsersQueue() const {
        std::string url = Endpoints::PLAYER + "/queue";

       return fetchAndParse<QueueObject>(url);
    }

    // --- POST ---
    void PlayerAPI::skipToNext(const std::optional<std::string>& device_id) const {
        skipHelper(true, std::move(device_id));
    }

    void PlayerAPI::skipToPrevious(const std::optional<std::string>& device_id) const {
        skipHelper(false, std::move(device_id));
    }

    void PlayerAPI::addItemToQueue(
        const std::string& uri,
        const std::optional<std::string> &device_id) const
    {
        std::string url = Endpoints::PLAYER + "/queue?uri=" + WebTools::urlEncode(uri);

        if (device_id.has_value() && !device_id->empty()) {
            url += "&device_id=" + *device_id;
        }

        (void)sendAction("POST", url, "");
    }

    // --- PUT ---
    void PlayerAPI::transferPlayback(
        const std::vector<std::string>& device_ids,
        const std::optional<bool>& play) const
    {
        if (device_ids.size() != 1) {
            throw Spotify::LogicException("Device Ids size must be 1");
        }

        nlohmann::json j;
        j["device_ids"] = device_ids;

        if (play.has_value()) {
            j["play"] = *play;
        }

       (void)sendAction("PUT", Endpoints::PLAYER, j.dump());
    }

    void PlayerAPI::startPlayback(
        const std::optional<std::string>& device_id,
        const std::optional<StartPlaybackProperties>& properties) const
    {
        std::string url = Endpoints::PLAYER + "/play";
        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        std::string body = "";
        if (properties.has_value()) {
            const auto& props = *properties;
            nlohmann::json j = nlohmann::json::object();

            if (props.context_uri) j["context_uri"] = *props.context_uri;
            if (props.uris)  j["uris"] = *props.uris;

            if (props.offset) {
                try {
                    j["offset"]["position"] = std::stoi(props.offset->position);
                } catch (...) {
                    j["offset"]["position"] = props.offset->position;
                }
            }

            j["position_ms"] = props.position_ms;

            body = j.dump();
        }

        (void)sendAction("PUT", url, body);
    }

    void PlayerAPI::pausePlayback(const std::optional<std::string> &device_id) const {

        std::string url = Endpoints::PLAYER + "/pause";
        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }

    void PlayerAPI::seekToPosition(
        const int& position_ms,
        const std::optional<std::string>& device_id) const
    {
        std::string url = Endpoints::PLAYER + "/seek?position_ms=" + WebTools::urlEncode(std::to_string(position_ms));
        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }

    void PlayerAPI::setRepeatMode(
        const RepeatState& state,
        const std::optional<std::string> &device_id) const
    {
        std::string repeat_state;
        switch (state) {
            case (RepeatState::Context): repeat_state = "context"; break;
            case (RepeatState::Track):   repeat_state = "track"; break;
            case (RepeatState::Off):     repeat_state = "off"; break;
            default:                     repeat_state = "off"; break;

        }

        std::string url = Endpoints::PLAYER + "/repeat?state=" + WebTools::urlEncode(repeat_state);
        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }

    void PlayerAPI::setPlaybackVolume(
        const int& volume_percent,
        const std::optional<std::string>& device_id) const
    {
        std::string url = Endpoints::PLAYER + "/volume?volume_percent=" + WebTools::urlEncode(std::to_string(volume_percent));
        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }

    void PlayerAPI::togglePlaybackShuffle(
        const bool& state,
        const std::optional<std::string>& device_id) const
    {
        std::string url = Endpoints::PLAYER + "/shuffle?state=" + (state ? "true" : "false");;

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }


    // --- PRIVATE ---
    void PlayerAPI::skipHelper(
        const bool& is_next,
        const std::optional<std::string>& device_id) const
    {
        std::string url = Endpoints::PLAYER + "/previous";
        if (is_next)
            url = Endpoints::PLAYER + "/next";

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        (void)sendAction("PUT", url, "");
    }
}