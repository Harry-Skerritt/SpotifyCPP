//
// Created by Harry Skerritt on 22/12/2025.
//

#include <utility>

#include "spotify/api/AudiobookAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<AudiobookObject> AudiobookAPI::getAudiobook(const std::string &id, std::optional<std::string> market) const {

        std::string url = BASE_AUDIOBOOK_URL + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

       return fetchAndParse<AudiobookObject>(url);
    }

    std::optional<AudiobookListObject> AudiobookAPI::getMultipleAudiobooks(const std::vector<std::string> &ids, std::optional<std::string> market) const {

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_AUDIOBOOK_URL + "?ids=" + id_list;

        return fetchAndParse<AudiobookListObject>(url);
    }

    std::optional<PagedChapterObject> AudiobookAPI::getAudiobookChapters(const std::string &id, std::optional<std::string> market, std::optional<int> limit, std::optional<int> offset) const {

        std::string url = BASE_AUDIOBOOK_URL + "/" + WebTools::urlEncode(id) + "/chapters";

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

        return fetchAndParse<PagedChapterObject>(url);

    }

    std::optional<PagedAudiobookObject> AudiobookAPI::getUsersSavedAudiobooks(std::optional<int> limit, std::optional<int> offset) const {

        std::string url = BASE_AUDIOBOOK_USER_URL;

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

        return fetchAndParse<PagedAudiobookObject>(url);

    }

    std::optional<std::vector<bool> > AudiobookAPI::checkUsersSavedAudiobooks(std::vector<std::string> ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_AUDIOBOOK_USER_URL + "/contains?ids=" + id_list;

        return fetchAndParse<std::vector<bool>>(url);
    }

    // --- PUT ---
    void AudiobookAPI::saveAudiobookForUser(std::vector<std::string> ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 50 IDs." << std::endl;
            return;
        }

        std::string url = BASE_AUDIOBOOK_USER_URL + "?ids=" + id_list;

        sendAction("PUT", url);
    }

    // --- DELETE ---
    void AudiobookAPI::removeUsersSavedAudiobooks(std::vector<std::string> ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 50 IDs." << std::endl;
            return;
        }

        std::string url = BASE_AUDIOBOOK_USER_URL + "?ids=" + id_list;

        nlohmann::json j;
        j["ids"] = id_list;

        sendAction("DELETE", url, j.dump());
    }





}