//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/ChapterAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"


namespace Spotify {

    // --- GET ---
    std::optional<ChapterObject> ChapterAPI::getChapter(const std::string &id, const std::optional<std::string> &market) const {

        std::string url = BASE_CHAPTER_URL + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty()) {
            url += "?market=" +  WebTools::urlEncode(*market);
        }

        return fetchAndParse<ChapterObject>(url);
    }

    std::optional<ChapterListObject> ChapterAPI::getMultipleChapters(const std::vector<std::string> &ids, const std::optional<std::string> &market) const {

        std::string id_list = Tools::toCSV(ids, 0, 50);

        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 50 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_CHAPTER_URL + "?ids=" + id_list;

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<ChapterListObject>(url);

    }



}
