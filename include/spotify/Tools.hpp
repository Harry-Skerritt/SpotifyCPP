//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TOOLS_H
#define TOOLS_H

#include <random>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

#include <spotify/Types.h>

namespace Spotify::WebTools {
    std::string generateRandomState(size_t length = 16);
    std::string urlEncode(const std::string &value);
    std::string extractValue(const std::string &json, const std::string &key);
    int extractIntValue(const std::string &json, const std::string &key);
}

namespace Spotify::Tools {
    void loadEnv(const std::string& filename = ".env");
    std::string stringifyResponse(ResponseCode code);
}



#endif //TOOLS_H
