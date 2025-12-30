//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef PLAYERAPI_H
#define PLAYERAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class PlayerAPI : public BaseAPI {
    // Funcs
    public:

        explicit PlayerAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves the current playback state
        /// @param market ISO 3166-1 country code (optional)
        /// @param additional_types The type of item to return (optional)
        /// @note Requires @c user-read-playback-state scope
        [[nodiscard]] std::optional<PlaybackObject> getPlaybackState(
            const std::optional<std::string> &market = std::nullopt,
            const std::optional<std::string> &additional_types = std::nullopt
        ) const;

        /// Retrieves a list of all available devices
        /// @note Requires @c user-read-playback-state scope
        [[nodiscard]] DeviceListObject getAvailableDevices() const;

        /// Retrieves the currently playing track of the current user
        /// @param market ISO 3166-1 country code (optional)
        /// @param additional_types Item type to return (optional)
        /// @note Requires @c user-read-currently-playing scope
        [[nodiscard]] std::optional<PlaybackObject> getCurrentlyPlayingTrack(
            const std::optional<std::string> &market = std::nullopt,
            const std::optional<std::string> &additional_types = std::nullopt
        ) const;

        /// Retrieves the previously played tracks by the current user
        /// @param limit Max number of items to return (optional)
        /// @param after Timestamp (Unix) to fetch tracks after (optional)
        /// @param before Timestamp (Unix) to fetch tracks before (optional)
        /// @note Requires @c user-read-recently-played scope
        [[nodiscard]] RecentlyPlayedTracksObject getRecentlyPlayedTracks(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int64_t>& after = std::nullopt,
            const std::optional<int64_t>& before = std::nullopt
        ) const;


        /// Retrieve the current users queue
        /// @note Requires @c user-read-playback-state scope
        /// @note Requires @c user-read-currently-playing scope
        [[nodiscard]] QueueObject getUsersQueue() const;

        // POST
        /// Skip to the next track in the current users queue
        /// @note Requires @c user-modify-playback-state scope
        void skipToNext(const std::optional<std::string>& device_id = std::nullopt) const;

        /// Skip to the previous track in the current users queue
        /// @note Requires @c user-modify-playback-state scope
        void skipToPrevious(const std::optional<std::string>& device_id = std::nullopt) const;

        /// Add a Spotify track to the current users queue
        /// @param uri URI of track of episode to add
        /// @param device_id ID of target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void addItemToQueue(
            const std::string& uri,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        // PUT
        /// Transfer playback to another device
        /// @param device_ids Device ID of the new device
        /// @param play Optionally start playback (optional)
        /// @note Requires @c user-modify-playback-state scope
        void transferPlayback(
            const std::vector<std::string>& device_ids,
            const std::optional<bool>& play = std::nullopt
        ) const;

        /// Start/Resume playback on the current users active device
        /// @param device_id Device ID of the target device (optional)
        /// @param properties Properties of a new context (Optional)
        /// @note Requires @c user-modify-playback-state scope
        void startPlayback(
            const std::optional<std::string>& device_id = std::nullopt,
            const std::optional<StartPlaybackProperties>& properties = std::nullopt
        ) const;

        /// Pause playback on the current users account
        /// @param device_id Device ID of the target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void pausePlayback(const std::optional<std::string> &device_id = std::nullopt) const;

        /// Skip to a give point i the users currently playing track
        /// @param position_ms Time (ms) to skip to
        /// @param device_id Device ID of the target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void seekToPosition(
            const int& position_ms,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        /// Change the current users repeat mode
        /// @param state New repeat mode
        /// @param device_id Device ID of the target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void setRepeatMode(
            const RepeatState& state,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        /// Change the volume for the users currently active device
        /// @param volume_percent New volume level (0-100)
        /// @param device_id Device ID of the target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void setPlaybackVolume(
            const int& volume_percent,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;

        /// Set shuffle state for the current user
        /// @param state New shuffle state (true/false)
        /// @param device_id Device ID of the target device (optional)
        /// @note Requires @c user-modify-playback-state scope
        void togglePlaybackShuffle(
            const bool& state,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;


    private:
        void skipHelper(
            const bool& is_next,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;
    };

}





#endif //PLAYERAPI_H
