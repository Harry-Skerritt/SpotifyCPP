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
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/average?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);
            const std::string avgHex = j.at("average").get<std::string>();
            return parseHex(avgHex);
        }catch (const std::exception& e) {
            throw Spotify::Exception("VisualAPI: Failed to parse average colour: " + std::string(e.what()));
        }
    }

    Colour VisualAPI::getAverageColour(const Spotify::ImageObject &image) {
        return getAverageColour(image.url);
    }


    // --- Average Colour Palette ---
    AveragePalette VisualAPI::getAverageImagePalette(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/average?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);

            return AveragePalette {
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

    AveragePalette VisualAPI::getAverageImagePalette(const Spotify::ImageObject &image) {
        return getAverageImagePalette(image.url);
    }


    // --- Vibrant Colour ---
    Colour VisualAPI::getVibrantColour(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/vibrant?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);
            const std::string avgHex = j.at("vibrant").get<std::string>();
            return parseHex(avgHex);
        }catch (const std::exception& e) {
            throw Spotify::Exception("VisualAPI: Failed to parse vibrant colour: " + std::string(e.what()));
        }
    }

    Colour VisualAPI::getVibrantColour(const Spotify::ImageObject &image) {
        return getVibrantColour(image.url);
    }


    // --- Vibrant Colour Palette ---
    VibrantPalette VisualAPI::getVibrantImagePalette(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/vibrant?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        try {
            auto j = nlohmann::json::parse(response.body);

            return VibrantPalette {
                parseHex(j.at("vibrant").get<std::string>()),
                parseHex(j.at("darker_1").get<std::string>()),
                parseHex(j.at("darker_2").get<std::string>()),
                parseHex(j.at("lighter_1").get<std::string>()),
                parseHex(j.at("lighter_2").get<std::string>()),
            };
        }catch (const std::exception& e) {
            throw Spotify::Exception("VisualAPI: Failed to parse vibrant colour palette: " + std::string(e.what()));
        }
    }

    VibrantPalette VisualAPI::getVibrantImagePalette(const Spotify::ImageObject &image) {
        return getVibrantImagePalette(image.url);
    }
}
