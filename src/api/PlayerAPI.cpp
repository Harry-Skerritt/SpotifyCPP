//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/api/PlayerAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"

Spotify::PlayerAPI::PlayerAPI(Client *client) : m_client(client) { }

std::optional<Spotify::PlaybackObject> Spotify::PlayerAPI::getCurrentlyPlayingTrack() const {
    if (!m_client) return std::nullopt;

    std::string token;
    try {
        token = m_client->getAccessToken();
    } catch (...) {
        std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
        throw;
    }


    auto result = HTTP::get((BASE_PLAYER_URL + "currently-playing"), token);


    if (result.code == RFC2616_Code::NO_CONTENT) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    if (result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }


    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::PlaybackObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }

    return std::nullopt;
}

