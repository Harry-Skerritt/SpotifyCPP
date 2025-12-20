//
// Created by Harry Skerritt on 20/12/2025.
//

#include "spotify/Tools.hpp"

std::string Spotify::WebTools::generateRandomState(size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return oss.str();
}

std::string Spotify::WebTools::urlEncode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (isalnum((unsigned char)c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::uppercase << std::setw(2) << int((unsigned char)c) << std::nouppercase;
        }
    }

    return escaped.str();
}

std::string Spotify::WebTools::extractValue(const std::string &json, const std::string &key) {
    std::string searchKey = "\"" + key + "\":\"";
    size_t start = json.find(searchKey);
    if (start == std::string::npos) return "";

    start += searchKey.length();
    size_t end = json.find("\"", start);
    return json.substr(start, end - start);
}

int Spotify::WebTools::extractIntValue(const std::string &json, const std::string &key) {
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = json.find(searchKey);
    if (keyPos == std::string::npos) return 0;

    size_t colonPos = json.find(":", keyPos + searchKey.length());
    if (colonPos == std::string::npos) return 0;

    size_t start = json.find_first_of("-0123456789", colonPos);
    if (start == std::string::npos) return 0;

    size_t end = json.find_first_not_of("0123456789", start);

    std::string valStr = json.substr(start, end - start);
    try {
        return std::stoi(valStr);
    } catch (...) {
        return 0;
    }
}

void Spotify::Tools::loadEnv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        setenv(key.c_str(), value.c_str(), 1); // overwrite if exists
    }
}

std::string Spotify::Tools::stringifyResponse(ResponseCode code) {
    switch(code) {
        case(SUCCESS):
            return "SUCCESS";
        case(NETWORK_ERROR):
            return "NETWORK_ERROR";
        case(AUTH_ERROR):
            return "AUTH_ERROR";
        case(PARSE_ERROR):
            return "PARSE_ERROR";
        default:
            return "UNKNOWN";
    }

}
