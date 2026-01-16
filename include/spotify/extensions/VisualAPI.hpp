//
// Created by Harry Skerritt on 08/01/2026.
//

#ifndef VISUALAPI_H
#define VISUALAPI_H

#include <spotify/internal.hpp>
#include "VisualModels.hpp"

namespace Spotify::Extensions {

    class VisualAPI {

    public:
        static Colour getAverageColour(const Spotify::ImageObject& image);
        static Colour getAverageColour(const std::string& imageUrl);

        static AveragePalette getAverageImagePalette(const Spotify::ImageObject& image);
        static AveragePalette getAverageImagePalette(const std::string& imageUrl);

        static Colour getVibrantColour(const Spotify::ImageObject& image);
        static Colour getVibrantColour(const std::string& imageUrl);

        static VibrantPalette getVibrantImagePalette(const Spotify::ImageObject& image);
        static VibrantPalette getVibrantImagePalette(const std::string& imageUrl);

    private:
        static Colour parseHex(const std::string& hexStr);

    };

}

#endif//VISUALAPI_H
