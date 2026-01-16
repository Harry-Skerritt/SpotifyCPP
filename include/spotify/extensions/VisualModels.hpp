#pragma once
#include <cstdint>
#include <iomanip>
#include <string>
#include <sstream>


namespace Spotify::Extensions {
    struct Colour {
        uint8_t r, g, b;
        [[nodiscard]] inline std::string toHex() const;
        [[nodiscard]] inline uint32_t to0x() const;
    };

    struct AveragePalette {
        Colour average;
        Colour darker_1;
        Colour darker_2;
        Colour lighter_1;
        Colour lighter_2;
    };

    struct VibrantPalette {
        Colour vibrant;
        Colour darker_1;
        Colour darker_2;
        Colour lighter_1;
        Colour lighter_2;
    };


    // Imp
    inline std::string Colour::toHex() const {
        std::stringstream ss;
        ss << "#" << std::hex << std::setfill('0')
            << std::setw(2) << static_cast<int>(r)
            << std::setw(2) << static_cast<int>(g)
            << std::setw(2) << static_cast<int>(b);
        return ss.str();
    }

    inline uint32_t Colour::to0x() const {
        return
            (static_cast<uint32_t>(r) << 16) |
            (static_cast<uint32_t>(g) << 8) |
            static_cast<uint32_t>(b);
    }


}

