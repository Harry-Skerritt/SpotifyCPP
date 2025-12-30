//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TOOLS_H
#define TOOLS_H

#pragma once


#include <random>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

#include "../models/Types.hpp"

namespace Spotify::WebTools {
    std::string generateRandomState(size_t length = 16);
    std::string urlEncode(const std::string &value);
    std::string extractValue(const std::string &json, const std::string &key);
    int extractIntValue(const std::string &json, const std::string &key);
    std::string getHttpStatusText(int code);
}

namespace Spotify::Tools {
    void loadEnv(const std::string& filename = ".env");


    bool inRange(int test_case, int low, int high);
    std::string toCSV(std::vector<std::string> ids, int min_qty = 0, int max_qty = 10);
    bool isValidMarket(std::string market);

    /// @brief Creates an ISO 8601 formatted timestamp
    /// Example: 2023-01-15T14:30:00Z
    std::string getISOTimestamp();

    /// @brief Formats milliseconds into a "M:SS" string.
    /// Example: 185000ms -> "3:05"
    /// @param ms Time in milliseconds
    std::string formatMs(long long ms);

    // Vars
    inline std::string valid_markets[185] = {
        "AD","AE","AG","AL","AM","AO","AR","AT","AU","AZ",
        "BA","BB","BD","BE","BF","BG","BH","BI","BJ","BN",
        "BO","BR","BS","BT","BW","BY","BZ","CA","CD","CG",
        "CH","CI","CL","CM","CO","CR","CV","CW","CY","CZ",
        "DE","DJ","DK","DM","DO","DZ","EC","EE","EG","ES",
        "ET","FI","FJ","FM","FR","GA","GB","GD","GE","GH",
        "GM","GN","GQ","GR","GT","GW","GY","HK","HN","HR",
        "HT","HU","ID","IE","IL","IN","IQ","IS","IT","JM",
        "JO","JP","KE","KG","KH","KI","KM","KN","KR","KW",
        "KZ","LA","LB","LC","LI","LK","LR","LS","LT","LU",
        "LV","LY","MA","MC","MD","ME","MG","MH","MK","ML",
        "MN","MO","MR","MT","MU","MV","MW","MX","MY","MZ",
        "NA","NE","NG","NI","NL","NO","NP","NR","NZ","OM",
        "PA","PE","PG","PH","PK","PL","PR","PS","PT","PW",
        "PY","QA","RO","RS","RW","SA","SB","SC","SE","SG",
        "SI","SK","SL","SM","SN","SR","ST","SV","SZ","TD",
        "TG","TH","TJ","TL","TN","TO","TR","TT","TV","TW",
        "TZ","UA","UG","US","UY","UZ","VC","VE","VN","VU",
        "WS","XK","ZA","ZM","ZW"
    };
}



#endif //TOOLS_H
