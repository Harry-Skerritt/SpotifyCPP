//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/EpisodeAPI.hpp"
#include "spotify/core/Endpoints.hpp"
#include "spotify/util/Tools.hpp"

#include "nlohmann/json.hpp"


namespace Spotify {

    // --- GET ---
    EpisodeObject EpisodeAPI::getEpisode(
        const std::string &id,
        const std::optional<std::string> &market) const
    {

        std::string url = Endpoints::EPISODES + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<EpisodeObject>(url);
    }

    EpisodeListObject EpisodeAPI::getMultipleEpisodes(
        const std::vector<std::string> &ids,
        const std::optional<std::string>& market) const
    {

        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::EPISODES + "?ids=" + id_list;

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<EpisodeListObject>(url);
    }

    PagedSavedEpisodeObject EpisodeAPI::getUsersSavedEpisodes(
        const std::optional<std::string> &market,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::MY_EPISODES;

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

        return fetchAndParse<PagedSavedEpisodeObject>(url);
    }

    std::vector<bool> EpisodeAPI::checkUsersSavedEpisodes(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 20);

        std::string url = Endpoints::MY_EPISODES + "/contains?ids=" + id_list;

        return fetchAndParse<std::vector<bool>>(url);
    }

    // --- PUT ---
    void EpisodeAPI::saveEpisodeForUser(const std::vector<std::string>& ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::MY_EPISODES + "?ids=" + id_list;

        (void)sendAction("PUT", url);
    }

    // --- DELETE --
    void EpisodeAPI::removeUserSavedEpisodes(const std::vector<std::string>& ids) const {

        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::MY_EPISODES + "?ids=" + id_list;

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("DELETE", url, j.dump());

    }








}