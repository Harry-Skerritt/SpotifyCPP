//
// Created by Harry Skerritt on 08/01/2026.
//

#include "./spotify/extensions/VisualAPI.hpp"

namespace Spotify::Extensions {

    // Helper
    Colour VisualAPI::parseHex(const std::string& hexStr) {
        if (hexStr.length() < 8) return {0, 0, 0};

        uint32_t value;
        std::stringstream ss;
        ss << std::hex << hexStr.substr(2); // Skips 0x
        ss >> value;

        return Colour {
            static_cast<uint8_t>((value >> 16) & 0xFF),
            static_cast<uint8_t>((value >> 8) & 0xFF),
            static_cast<uint8_t>(value & 0xFF)
        };
    }

    // --- Average Colour ---
    Colour VisualAPI::getAverageColour(const std::string &imageUrl) {
        std::string encodedImageUrl = detail::urlEncode(imageUrl);
        std::string requestUrl = "https://avaerage-color-api.vercel.app/api/analyse?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);
            std::string avgHex = j.at("average").get<std::string>();
            return parseHex(avgHex);
        }catch (const std::exception& e) {
            throw Spotify::Exception("VisualAPI: Failed to parse average colour: " + std::string(e.what()));
        }
    }

    Colour VisualAPI::getAverageColour(const Spotify::ImageObject &image) {
        return getAverageColour(image.url);
    }


    // --- Colour Palette ---
    ImagePalette VisualAPI::getImagePalette(const std::string &imageUrl) {
        std::string encodedImageUrl = detail::urlEncode(imageUrl);
        std::string requestUrl = "https://avaerage-color-api.vercel.app/api/analyse?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);

            return ImagePalette {
                parseHex(j.at("average").get<std::string>()),
                parseHex(j.at("darker_1").get<std::string>()),
                parseHex(j.at("darker_2").get<std::string>()),
                parseHex(j.at("lighter_1").get<std::string>()),
                parseHex(j.at("lighter_2").get<std::string>()),
            };
        }catch (const std::exception& e) {
            throw Spotify::Exception("VisualAPI: Failed to parse colour palette: " + std::string(e.what()));
        }
    }

    ImagePalette VisualAPI::getImagePalette(const Spotify::ImageObject &image) {
        return getImagePalette(image.url);
    }

}