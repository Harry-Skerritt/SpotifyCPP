//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

namespace Spotify {

    struct ClientCredentials {
        std::string client_id;
        std::string client_secret;
    };

    enum ResponseCode {
        SUCCESS,
        NETWORK_ERROR,
        AUTH_ERROR,
        PARSE_ERROR,
        VALUE_ERROR,
        UNKNOWN_ERROR
    };

    struct AuthResponse {
        std::string access_token;
        std::string token_type;
        std::string scope;
        std::chrono::time_point<std::chrono::system_clock> expire_time;
        std::string refresh_token;
        ResponseCode response_code;
    };

    enum class RFC2616_Code {
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        NO_CONTENT = 204,
        NOT_MODIFIED = 304,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        TOO_MANY_REQUESTS = 429,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        BAD_GATEWAY = 502,
        SERVICE_UNAVAILABLE = 503,
        NETWORK_ERROR = -1,
        UNKNOWN_ERROR = -2,
    };


    // Todo: Investigate Categories
    // Todo: See if any other forward declarations can be made for readability
    struct EpisodeObject;
    struct TrackObject;
    struct ArtistObject;
    struct AlbumObject;

    template <typename T>
    struct PagingObject {
        std::string href;
        int limit{};
        std::optional<std::string> next;
        int offset{};
        std::optional<std::string> prev;
        int total{};
        std::vector<T> items;
    };

    // --- 'Base' Objects ---
    struct ImageObject {
        std::string url;
        std::optional<int> height;
        std::optional<int> width;
    };

    struct CopyrightObject {
        std::string text;
        std::string type;
    };

    struct ExternalURL {
        std::string spotify;
    };

    struct RestrictionsObject {
        std::string reason;
    };

    struct ExternalID {
        std::string isrc;
        std::string ean;
        std::string upc;
    };

    struct LinkedFromObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
    };

    struct FollowersObject {
        std::optional<std::string> href;
        int total;
    };

    struct ResumePointObject {
        bool fully_played;
        int resume_position_ms;
    };

    struct NarratorObject {
        std::string name;
    };

    struct AuthorObject {
        std::string name;
    };

    struct CategoryObject {
        std::string href;
        std::vector<ImageObject> icons;
        std::string id;
        std::string name;
    };

    struct GenreObject { // Dep
        std::vector<std::string> genres;
    };

    struct MarketObject {
        std::vector<std::string> markets;
    };

    struct DeviceObject {
        std::optional<std::string> id;
        bool is_active;
        bool is_private_session;
        bool is_restricted;
        std::string name;
        std::string type;
        std::optional<int> volume_percent;
        bool supports_volume;
    };

    struct ContextObject {
        std::string type;
        std::string href;
        ExternalURL external_urls;
        std::string uri;
    };

    struct ActionsObject {
        bool interrupting_playback;
        bool pausing;
        bool resuming;
        bool seeking;
        bool skipping_next;
        bool skipping_prev;
        bool toggling_repeat_context;
        bool toggling_shuffle;
        bool toggling_repeat_track;
        bool transferring_playback;
    };

    struct ExplicitContentObject {
        bool filter_enabled;
        bool filter_locked;
    };

    struct AddedByObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
    };

    struct OwnerObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
        std::optional<std::string> display_name;
    };

    struct TrackCollectionObject {
        std::string href;
        int total;
    };


    // --- Simplified Objects ---
    struct SimplifiedArtistObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string name;
        std::string type;
        std::string uri;
    };

    struct SimplifiedTrackObject {
        std::vector<SimplifiedArtistObject> artists;
        std::vector<std::string> available_markets;
        int disc_number;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        bool is_playable;
        LinkedFromObject linked_from;
        RestrictionsObject restrictions;
        std::string name;
        std::optional<std::string> preview_url; // Dep
        int track_number;
        std::string type;
        std::string uri;
        bool is_local;
    };

    struct SimplifiedChapterObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::vector<std::string> available_markets;
        int chapter_number;
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_playable;
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
    };

    struct SimplifiedAudioBookObject {
        std::vector<AuthorObject> authors;
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        std::string edition;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::vector<NarratorObject> narrators;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_chapters;
    };

    struct SimplifiedEpisodeObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        bool is_playable;
        std::string language; // Dep
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
    };

    struct SimplifiedShowObject {
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_episodes;
    };

    struct SimplifiedPlaylistObject {
        bool collaborative;
        std::string description;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        OwnerObject owner;
        bool is_public;
        std::string snapshot_id;
        TrackCollectionObject tracks;
        std::string type;
        std::string uri;
    };

    struct SimplifiedAlbumObject {
        std::string album_type;
        int total_tracks;
        std::vector<std::string> available_markets;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        RestrictionsObject restrictions;
        std::string type;
        std::string uri;
        std::vector<SimplifiedArtistObject> artists;
    };


    // -- Linked Objects --
    struct PlaylistTrackObject {
        std::string added_at;
        AddedByObject added_by;
        bool is_local;
        std::variant<std::shared_ptr<TrackObject>, std::shared_ptr<EpisodeObject>> track;
    };

    using LinkedTracksObject = PagingObject<SimplifiedTrackObject>;
    using LinkedChaptersObject = PagingObject<SimplifiedChapterObject>;
    using LinkedEpisodesObject = PagingObject<SimplifiedEpisodeObject>;
    using LinkedPlaylistTracksObject = PagingObject<PlaylistTrackObject>;


    // --- 'Main' Response Objects --
    struct AlbumObject {
        std::string album_type;
        int total_tracks;
        std::vector<std::string> available_markets;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        RestrictionsObject restrictions;
        std::string type;
        std::string uri;
        std::vector<SimplifiedArtistObject> artists;
        LinkedTracksObject tracks;
        std::vector<CopyrightObject> copyrights;
        ExternalID external_ids;
        std::vector<std::string> genres; // dep
        std::string label;
        int popularity;
    };

    struct ArtistObject {
        ExternalURL external_urls;
        FollowersObject followers;
        std::vector<std::string> genres;
        std::string href;
        std::vector<ImageObject> images;
        std::string name;
        int popularity;
        std::string type;
        std::string uri;
    };

    struct TrackObject {
        AlbumObject album;
        std::vector<SimplifiedArtistObject> artists;
        std::vector<std::string> available_markets;
        int disc_number;
        int duration_ms;
        bool is_explicit;
        ExternalID external_ids;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        bool is_playable;
        LinkedFromObject linked_from;
        RestrictionsObject restrictions;
        std::string name;
        int popularity;
        std::optional<std::string> preview_url; // Dep
        int track_number;
        std::string type;
        std::string uri;
        bool is_local;
    };

    struct AudioBookObject {
        std::vector<AuthorObject> authors;
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        std::string edition;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::vector<NarratorObject> narrators;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_chapters;
        LinkedChaptersObject chapters;
    };

    struct ChapterObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::vector<std::string> available_markets;
        int chapter_number;
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_playable;
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
        SimplifiedAudioBookObject audiobook;
    };

    struct EpisodeObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        bool is_playable;
        std::string language; // Dep
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
        SimplifiedShowObject show;
    };

    struct ShowObject {
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_episodes;
        LinkedEpisodesObject episodes;
    };

    struct PlaybackObject {
        DeviceObject device;
        std::string repeat_state;
        bool shuffle_state;
        ContextObject context;
        long long timestamp;
        int progress_ms;
        bool is_playing;
        std::variant<std::shared_ptr<TrackObject>, std::shared_ptr<EpisodeObject>> item;
        std::string currently_playing_type;
        ActionsObject actions;
    };


    struct PlaylistObject {
        bool collaborative;
        std::optional<std::string> description;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        OwnerObject owner;
        bool is_public;
        std::string snapshot_id;
        LinkedPlaylistTracksObject tracks;
        std::string type;
        std::string uri;
    };

    struct UserObject {
        std::string country;
        std::string display_name;
        std::string email;
        ExplicitContentObject explicit_content;
        ExternalURL external_urls;
        FollowersObject followers;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string product;
        std::string type;
        std::string uri;
    };


    // --- Search --
    using SearchTrackObject = PagingObject<TrackObject>;
    using SearchArtistObject = PagingObject<ArtistObject>;
    using SearchAlbumObject = PagingObject<SimplifiedAlbumObject>;
    using SearchPlaylistObject = PagingObject<SimplifiedPlaylistObject>;
    using SearchShowsObject = PagingObject<SimplifiedShowObject>;
    using SearchEpisodesObject = PagingObject<SimplifiedEpisodeObject>;
    using SearchAudioBookObject = PagingObject<SimplifiedAudioBookObject>;

    struct SearchObject {
        std::optional<SearchTrackObject> tracks;
        std::optional<SearchArtistObject> artists;
        std::optional<SearchAlbumObject> albums;
        std::optional<SearchPlaylistObject> playlists;
        std::optional<SearchShowsObject> shows;
        std::optional<SearchEpisodesObject> episodes;
        std::optional<SearchAudioBookObject> audiobook;
    };

}

#endif //TYPES_H
