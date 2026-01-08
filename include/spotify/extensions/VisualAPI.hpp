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

        static ImagePalette getImagePalette(const Spotify::ImageObject& image);
        static ImagePalette getImagePalette(const std::string& imageUrl);

    private:
        static Colour parseHex(const std::string& hexStr);

    };

}

#endif//VISUALAPI_H
