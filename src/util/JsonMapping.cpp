//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/util/JsonMapping.hpp"

namespace Spotify {
    template<typename T>
    void map_optional(const json &j, const std::string &key, std::optional<T> &field) {
        if (j.contains(key) && !j[key].is_null()) {
            field = j.at(key).get<T>();
        } else {
            field = std::nullopt;
        }
    }

    template<typename T>
    void map_object(const json& j, const std::string& key, T& field) {
        if (j.contains(key) && !j[key].is_null()) {
            field = j.at(key).get<T>();
        }
    }

    void map_queue_item(const nlohmann::json& j, Spotify::QueueObject::PlayableItem& target) {
        if (j.is_null()) return;

        std::string type = j.value("type", "");

        if (type == "track") {
            auto track = std::make_shared<Spotify::TrackObject>();
            from_json(j, *track);
            target.data = track;
        }
        else if (type == "episode") {
            auto ep = std::make_shared<Spotify::EpisodeObject>();
            from_json(j, *ep);
            target.data = ep;
        }
    }

    // --- Base Objects ---
    void from_json(const json &j, ImageObject &i) {
        i.url = j.value("url", "");
        map_optional(j, "width", i.width);
        map_optional(j, "height", i.height);
    }

    void from_json(const json &j, CursorObject &c) {
        c.after = j.value("after", "");
        c.before = j.value("before", "");
    }


    void from_json(const json &j, CopyrightObject &c) {
        c.text = j.value("text", "");
        c.type = j.value("type", "");
    }

    void from_json(const json &j, ExternalURL &e) {
        e.spotify = j.value("spotify", "");
    }

    void from_json(const json &j, RestrictionsObject &r) {
        r.reason = j.value("reason", "");
    }

    void from_json(const json &j, ExternalID &e) {
        e.isrc = j.value("isrc", "");
        e.ean = j.value("ean", "");
        e.upc = j.value("upc", "");
    }

    void from_json(const json &j, LinkedFromObject &l) {
        map_object(j, "external_urls", l.external_urls);
        l.href = j.value("href", "");
        l.id = j.value("id", "");
        l.type = j.value("type", "");
        l.uri = j.value("uri", "");
    }

    void from_json(const json &j, FollowersObject &f) {
        map_optional(j, "href", f.href);
        f.total = j.value("total", 0);
    }

    void from_json(const json &j, ResumePointObject &r) {
        r.fully_played = j.value("fully_played", false);
        r.resume_position_ms = j.value("resume_position_ms", 0);
    }

    void from_json(const json &j, NarratorObject &n) {
        n.name = j.value("name", "");
    }

    void from_json(const json &j, AuthorObject &a) {
        a.name = j.value("name", "");
    }

    void from_json(const json &j, CategoryObject &c) {
        c.icons = j.value("icons", std::vector<ImageObject>{});
        c.href = j.value("href", "");
        c.id = j.value("id", "");
        c.name = j.value("name", "");
    }

    void from_json(const json &j, GenreObject &g) {
        g.genres = j.value("genres", std::vector<std::string>{});
    }

    void from_json(const json &j, MarketObject &m) {
        m.markets = j.value("markets", std::vector<std::string>{});
    }

    void from_json(const json&j, DeviceObject& d) {
        map_optional(j, "id", d.id);
        d.is_active = j.value("is_active", false);
        d.is_private_session = j.value("is_private_session", false);
        d.is_restricted = j.value("is_restricted", false);
        d.name = j.value("name", "Unknown");
        d.type = j.value("type", "Unknown");
        map_optional(j, "volume_percent", d.volume_percent);
        d.supports_volume = j.value("supports_volume", false);
    }

    void from_json(const json &j, ContextObject &c) {
        c.type = j.value("type", "");
        c.href = j.value("href", "");
        c.uri = j.value("uri", "");
        map_object(j, "external_urls", c.external_urls);

    }

    void from_json(const json &j, ActionsObject &a) {
        const auto& dis = j.value("disallows", json::object());

        a.interrupting_playback = !dis.value("interrupting_playback", false);
        a.pausing = !dis.value("pausing", false);
        a.resuming = !dis.value("resuming", false);
        a.seeking = !dis.value("seeking", false);
        a.skipping_next = !dis.value("skipping_next", false);
        a.skipping_prev = !dis.value("skipping_prev", false);
        a.toggling_repeat_context = !dis.value("toggling_repeat_context", false);
        a.toggling_shuffle = !dis.value("toggling_shuffle", false);
        a.toggling_repeat_track = !dis.value("toggling_repeat_track", false);
        a.transferring_playback = !dis.value("transferring_playback", false);
    }

    void from_json(const json &j, ExplicitContentObject &e) {
        e.filter_enabled = j.value("filter_enabled", false);
        e.filter_locked = j.value("filter_locked", false);
    }

    void from_json(const json &j, AddedByObject &a) {
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
    }

    void from_json(const json &j, OwnerObject &o) {
        map_object(j, "external_urls", o.external_urls);
        o.href = j.value("href", "");
        o.id = j.value("id", "");
        o.type = j.value("type", "");
        o.uri = j.value("uri", "");
        map_optional(j, "display_name", o.display_name);
    }

    void from_json(const json &j, TrackCollectionObject &t) {
        t.href = j.value("href", "");
        t.total = j.value("total", 0);
    }


    // --- Simplified Objects ---
    void from_json(const json &j, SimplifiedArtistObject &a) {
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.name = j.value("name", "");
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
    }

    void from_json(const json &j, SimplifiedTrackObject &t) {
        t.artists = j.value("artists", std::vector<SimplifiedArtistObject>{});
        t.available_markets = j.value("available_markets", std::vector<std::string>{});
        t.disc_number = j.value("disc_number", 0);
        t.duration_ms = j.value("duration_ms", 0);
        t.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", t.external_urls);
        t.href = j.value("href", "");
        t.id = j.value("id", "");
        t.is_playable = j.value("is_playable", false);
        map_object(j, "linked_from", t.linked_from);
        map_object(j, "restrictions", t.restrictions);
        t.name = j.value("name", "");
        map_optional(j, "preview_url", t.preview_url);
        t.track_number = j.value("track_number", 0);
        t.type = j.value("type", "");
        t.uri = j.value("uri", "");
        t.is_local = j.value("is_local", false);
    }

    void from_json(const json &j, SimplifiedChapterObject &c) {
        map_optional(j, "audio_preview_url", c.audio_preview_url);
        c.available_markets = j.value("available_markets", std::vector<std::string>{});
        c.chapter_number = j.value("chapter_number", 0);
        c.description = j.value("description", "");
        c.html_description = j.value("html_description", "");
        c.duration_ms = j.value("duration_ms", 0);
        c.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", c.external_urls);
        c.href = j.value("href", "");
        c.id = j.value("id", "");
        c.images = j.value("images", std::vector<ImageObject>{});
        c.is_playable = j.value("is_playable", false);
        c.languages = j.value("languages", std::vector<std::string>{});
        c.name = j.value("name", "");
        c.release_date = j.value("release_date", "");
        c.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "resume_point", c.resume_point);
        c.type = j.value("type", "");
        c.uri = j.value("uri", "");
        map_object(j, "restrictions", c.restrictions);
    }

    void from_json(const json &j, SimplifiedAudiobookObject &a) {
        a.authors = j.value("authors", std::vector<AuthorObject>{});
        a.available_markets = j.value("available_markets", std::vector<std::string>{});
        a.copyrights = j.value("copyrights", std::vector<CopyrightObject>{});
        a.description = j.value("description", "");
        a.html_description = j.value("html_description", "");
        a.edition = j.value("edition", "");
        a.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.images = j.value("images", std::vector<ImageObject>{});
        a.languages = j.value("languages", std::vector<std::string>{});
        a.media_type = j.value("media_type", "");
        a.name = j.value("name", "");
        a.narrators = j.value("narrators", std::vector<NarratorObject>{});
        a.publisher = j.value("publisher", "");
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
        a.total_chapters = j.value("total_chapters", 0);
    }

    void from_json(const json &j, SimplifiedEpisodeObject &e) {
        map_optional(j, "audio_preview_url", e.audio_preview_url);
        e.description = j.value("description", "");
        e.html_description = j.value("html_description", "");
        e.duration_ms = j.value("duration_ms", 0);
        e.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", e.external_urls);
        e.href = j.value("href", "");
        e.id = j.value("id", "");
        e.images = j.value("images", std::vector<ImageObject>{});
        e.is_externally_hosted = j.value("is_externally_hosted", false);
        e.is_playable = j.value("is_playable", false);
        e.language = j.value("language", "");
        e.languages = j.value("languages", std::vector<std::string>{});
        e.name = j.value("name", "");
        e.release_date = j.value("release_date", "");
        e.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "resume_point", e.resume_point);
        e.type = j.value("type", "");
        e.uri = j.value("uri", "");
        map_object(j, "restrictions", e.restrictions);
    }

    void from_json(const json &j, SimplifiedShowObject &s) {
        s.available_markets = j.value("available_markets", std::vector<std::string>{});
        s.copyrights = j.value("copyrights", std::vector<CopyrightObject>{});
        s.description = j.value("description", "");
        s.html_description = j.value("html_description", "");
        s.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", s.external_urls);
        s.href = j.value("href", "");
        s.id = j.value("id", "");
        s.images = j.value("images", std::vector<ImageObject>{});
        s.is_externally_hosted = j.value("is_externally_hosted", false);
        s.languages = j.value("languages", std::vector<std::string>{});
        s.media_type = j.value("media_type", "");
        s.name = j.value("name", "");
        s.publisher = j.value("publisher", "");
        s.type = j.value("type", "");
        s.uri = j.value("uri", "");
        s.total_episodes = j.value("total_episodes", 0);
    }

    void from_json(const json &j, SimplifiedPlaylistObject &p) {
        p.collaborative = j.value("collaborative", false);
        p.description = j.value("description", "");
        map_object(j, "external_urls", p.external_urls);
        p.href = j.value("href", "");
        p.id = j.value("id", "");
        p.images = j.value("images", std::vector<ImageObject>{});
        p.name = j.value("name", "");
        map_object(j, "owner", p.owner);
        p.is_public = j.value("public", false);
        p.snapshot_id = j.value("snapshot_id", "");
        map_object(j, "tracks", p.tracks);
        p.type = j.value("type", "");
        p.uri = j.value("uri", "");
    }

    void from_json(const json &j, SimplifiedAlbumObject &a) {
        a.album_type = j.value("album_type", "");
        a.total_tracks = j.value("total_tracks", 0);
        a.available_markets = j.value("available_markets", std::vector<std::string>{});
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.images = j.value("images", std::vector<ImageObject>{});
        a.name = j.value("name", "");
        a.release_date = j.value("release_date", "");
        a.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "restrictions", a.restrictions);
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
        a.artists = j.value("artists", std::vector<SimplifiedArtistObject>{});
    }

    // --- Linked Objects ---
    void from_json(const nlohmann::json& j, PlaylistTrackObject& pt) {
        pt.added_at = j.value("added_at", "");
        if (j.contains("added_by")) pt.added_by = j.at("added_by").get<AddedByObject>();
        pt.is_local = j.value("is_local", false);

        // Handle Variant
        if (j.contains("track") && !j["track"].is_null()) {
            const auto& track_data = j.at("track");
            std::string type = track_data.value("type", "");

            if (type == "track") {
                auto t = std::make_shared<TrackObject>();
                track_data.get_to(*t); // Calls from_json(..., TrackObject&)
                pt.track = t;
            } else if (type == "episode") {
                auto e = std::make_shared<EpisodeObject>();
                track_data.get_to(*e); // Calls from_json(..., EpisodeObject&)
                pt.track = e;
            }
        }
    }

    template <typename T>
    void from_json(const nlohmann::json& j, PagingObject<T>& p) {
        p.href = j.value("href", "");
        p.limit = j.value("limit", 0);
        p.total = j.value("total", 0);

        map_optional(j, "offset", p.offset);
        map_optional(j, "next", p.next);
        map_optional(j, "prev", p.prev);

        map_optional(j, "cursors", p.cursors);

        p.items = j.value("items", std::vector<T>{});
    }


    // --- 'Main' Response Objects ---
    void from_json(const json &j, AlbumObject &a) {
        a.album_type = j.value("album_type", "");
        a.total_tracks = j.value("total_tracks", 0);
        a.available_markets = j.value("available_markets", std::vector<std::string>{});
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.images = j.value("images", std::vector<ImageObject>{});
        a.name = j.value("name", "");
        a.release_date = j.value("release_date", "");
        a.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "restrictions", a.restrictions);
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
        a.artists = j.value("artists", std::vector<SimplifiedArtistObject>{});
        map_object(j, "tracks", a.tracks);
        a.copyrights = j.value("copyrights", std::vector<CopyrightObject>{});
        map_object(j, "external_ids", a.external_ids);
        a.genres = j.value("genres", std::vector<std::string>{});
        a.label = j.value("label", "");
        a.popularity = j.value("popularity", 0);
    }

    void from_json(const json &j, ArtistObject &a) {
        map_object(j, "external_urls", a.external_urls);
        map_object(j, "followers", a.followers);
        a.genres = j.value("genres", std::vector<std::string>{});
        a.href = j.value("href", "");
        a.images = j.value("images", std::vector<ImageObject>{});
        a.name = j.value("name", "");
        a.popularity = j.value("popularity", 0);
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
    }

    void from_json(const json &j, TrackObject &a) {
        map_object(j, "album", a.album);
        a.artists = j.value("artists", std::vector<SimplifiedArtistObject>{});
        a.available_markets = j.value("available_markets", std::vector<std::string>{});
        a.disc_number = j.value("disc_number", 0);
        a.duration_ms = j.value("duration_ms", 0);
        a.is_explicit = j.value("explicit", false);
        map_object(j, "external_ids", a.external_ids);
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.is_playable = j.value("is_playable", false);
        map_object(j, "linked_from", a.linked_from);
        map_object(j, "restrictions", a.restrictions);
        a.name = j.value("name", "");
        a.popularity = j.value("popularity", 0);
        map_optional(j, "preview_url", a.preview_url);
        a.track_number = j.value("track_number", 0);
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
        a.is_local = j.value("is_local", false);
    }

    void from_json(const json &j, AudiobookObject &a) {
        a.authors = j.value("authors", std::vector<AuthorObject>{});
        a.available_markets = j.value("available_markets", std::vector<std::string>{});
        a.copyrights = j.value("copyrights", std::vector<CopyrightObject>{});
        a.description = j.value("description", "");
        a.html_description = j.value("html_description", "");
        a.edition = j.value("edition", "");
        a.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", a.external_urls);
        a.href = j.value("href", "");
        a.id = j.value("id", "");
        a.images = j.value("images", std::vector<ImageObject>{});
        a.languages = j.value("languages", std::vector<std::string>{});
        a.media_type = j.value("media_type", "");
        a.name = j.value("name", "");
        a.narrators = j.value("narrators", std::vector<NarratorObject>{});
        a.publisher = j.value("publisher", "");
        a.type = j.value("type", "");
        a.uri = j.value("uri", "");
        a.total_chapters = j.value("total_chapters", 0);
        map_object(j, "chapters", a.chapters);
    }

    void from_json(const json &j, ChapterObject &c) {
        map_optional(j, "audio_preview_url", c.audio_preview_url);
        c.available_markets = j.value("available_markets", std::vector<std::string>{});
        c.chapter_number = j.value("chapter_number", 0);
        c.description = j.value("description", "");
        c.html_description = j.value("html_description", std::string{});
        c.duration_ms = j.value("duration_ms", 0);
        c.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", c.external_urls);
        c.href = j.value("href", "");
        c.id = j.value("id", "");
        c.images = j.value("images", std::vector<ImageObject>{});
        c.is_playable = j.value("is_playable", false);
        c.languages = j.value("languages", std::vector<std::string>{});
        c.name = j.value("name", "");
        c.release_date = j.value("release_date", "");
        c.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "resume_point", c.resume_point);
        c.type = j.value("type", "");
        c.uri = j.value("uri", "");
        map_object(j, "restrictions", c.restrictions);
        map_object(j, "audiobook", c.audiobook);
    }

    void from_json(const json &j, EpisodeObject &e) {
        map_optional(j, "audio_preview_url", e.audio_preview_url);
        e.description = j.value("description", "");
        e.html_description = j.value("html_description", std::string{});
        e.duration_ms = j.value("duration_ms", 0);
        e.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", e.external_urls);
        e.href = j.value("href", "");
        e.id = j.value("id", "");
        e.images = j.value("images", std::vector<ImageObject>{});
        e.is_externally_hosted = j.value("is_externally_hosted", false);
        e.is_playable = j.value("is_playable", false);
        e.language = j.value("language", "");
        e.languages = j.value("languages", std::vector<std::string>{});
        e.name = j.value("name", "");
        e.release_date = j.value("release_date", "");
        e.release_date_precision = j.value("release_date_precision", "");
        map_object(j, "resume_point", e.resume_point);
        e.type = j.value("type", "");
        e.uri = j.value("uri", "");
        map_object(j, "restrictions", e.restrictions);
        map_object(j, "show", e.show);
    }

    void from_json(const json &j, ShowObject &s) {
        s.available_markets = j.value("available_markets", std::vector<std::string>{});
        s.copyrights = j.value("copyrights", std::vector<CopyrightObject>{});
        s.description = j.value("description", "");
        s.html_description = j.value("html_description", std::string{});
        s.is_explicit = j.value("explicit", false);
        map_object(j, "external_urls", s.external_urls);
        s.href = j.value("href", "");
        s.id = j.value("id", "");
        s.images = j.value("images", std::vector<ImageObject>{});
        s.is_externally_hosted = j.value("is_externally_hosted", false);
        s.languages = j.value("languages", std::vector<std::string>{});
        s.media_type = j.value("media_type", "");
        s.name = j.value("name", "");
        s.publisher = j.value("publisher", "");
        s.type = j.value("type", "");
        s.uri = j.value("uri", "");
        s.total_episodes = j.value("total_episodes", 0);
        map_object(j, "episodes", s.episodes);
    }

    void from_json(const json &j, PlaybackObject &p) {
        if (j.contains("device")) p.device = j.at("device").get<DeviceObject>();
        p.repeat_state = j.value("repeat_state", "");
        p.shuffle_state = j.value("shuffle_state", false);
        map_object(j, "context", p.context);
        p.timestamp = j.value("timestamp", 0LL);
        p.progress_ms = j.value("progress_ms", 0);
        p.is_playing = j.value("is_playing", false);
        p.currently_playing_type = j.value("currently_playing_type", "track");

        if (j.contains("item") && !j["item"].is_null()) {
            if (p.currently_playing_type == "track") {
                auto track = std::make_shared<TrackObject>();
                j.at("item").get_to(*track);
                p.item = track;
            } else if (p.currently_playing_type == "episode") {
                auto episode = std::make_shared<EpisodeObject>();
                j.at("item").get_to(*episode);
                p.item = episode;
            }
        }

        map_object(j, "actions", p.actions);
    }

    void from_json(const json &j, PlaylistObject &p) {
        p.collaborative = j.value("collaborative", false);
        map_optional(j, "description", p.description);
        map_object(j, "external_urls", p.external_urls);
        p.href = j.value("href", "");
        p.id = j.value("id", "");
        p.images = j.value("images", std::vector<ImageObject>{});
        p.name = j.value("name", "");
        map_object(j, "owner", p.owner);
        p.is_public = j.value("public", false);
        p.snapshot_id = j.value("snapshot_id", "");
        map_object(j, "tracks", p.tracks);
        p.type = j.value("type", "");
        p.uri = j.value("uri", "");
    }

    void from_json(const json &j, UserObject &u) {
        u.country = j.value("country", "");
        u.display_name = j.value("display_name", "");
        u.email = j.value("email", "");
        map_object(j, "explicit_content", u.explicit_content);
        map_object(j, "external_urls", u.external_urls);
        map_object(j, "followers", u.followers);
        u.href = j.value("href", "");
        u.id = j.value("id", "");
        u.images = j.value("images", std::vector<ImageObject>{});
        u.product = j.value("product", "");
        u.type = j.value("type", "");
        u.uri = j.value("uri", "");
    }

    void from_json(const json &j, PlayHistoryObject &p) {
        map_object(j, "track", p.track);
        p.played_at = j.value("played_at", "");
        map_object(j, "context", p.context);
    }

    void from_json(const json &j, QueueObject &q) {
        if (j.contains("currently_playing") && !j["currently_playing"].is_null()) {
            map_queue_item(j.at("currently_playing"), q.currently_playing);
        }


        q.queue.clear();
        if (j.contains("queue") && j.at("queue").is_array()) {
            for (const auto& item_json : j.at("queue")) {
                Spotify::QueueObject::PlayableItem item;
                map_queue_item(item_json, item);
                q.queue.push_back(item);
            }
        }
    }



    // --- Search ---
    void from_json(const json &j, SearchObject &s) {
        map_optional(j, "tracks", s.tracks);
        map_optional(j, "artists",s.artists);
        map_optional(j, "albums", s.albums);
        map_optional(j, "playlists", s.playlists);
        map_optional(j, "shows", s.shows);
        map_optional(j, "episodes", s.episodes);
        map_optional(j, "audiobooks", s.audiobook);
    }

    // --- List Objects ---
    void from_json(const json &j, DeviceListObject &dl) {
        dl.devices = j.value("devices", std::vector<DeviceObject>{});
    }

    void from_json(const json &j, AlbumListObject &al) {
        al.albums = j.value("albums", std::vector<AlbumObject>{});
    }

    void from_json(const json &j, ArtistListObject &al) {
        al.artists = j.value("artists", std::vector<ArtistObject>{});
    }

    void from_json(const json &j, AudiobookListObject &ab) {
        ab.audiobooks = j.value("audiobooks", std::vector<AudiobookObject>{});
    }

    void from_json(const json &j, ChapterListObject &cl) {
        cl.chapters = j.value("chapters", std::vector<ChapterObject>{});
    }


    void from_json(const json &j, TrackListObject &tl) {
        tl.tracks = j.value("tracks", std::vector<TrackObject>{});
    }


    void from_json(const json &j, SavedAlbumObject &s) {
        s.added_at = j.value("added_at", "");
        map_object(j, "album", s.album);
    }



    // --- Explicit Paging Implementation ---

    template void from_json<TrackObject>(const json& j, PagingObject<TrackObject>& p);
    template void from_json<SimplifiedChapterObject>(const json& j, PagingObject<SimplifiedChapterObject>& p);
    template void from_json<ArtistObject>(const json& j, PagingObject<ArtistObject>& p);
    template void from_json<SimplifiedAlbumObject>(const json& j, PagingObject<SimplifiedAlbumObject>& p);
    template void from_json<SimplifiedTrackObject>(const json& j, PagingObject<SimplifiedTrackObject>& p);
    template void from_json<PlaylistTrackObject>(const json& j, PagingObject<PlaylistTrackObject>& p);
    template void from_json<SavedAlbumObject>(const json& j, PagingObject<SavedAlbumObject>& p);
    template void from_json<PlayHistoryObject>(const json& j, PagingObject<PlayHistoryObject>& p);
    template void from_json<CategoryObject>(const json& j, PagingObject<CategoryObject>& p);

}

