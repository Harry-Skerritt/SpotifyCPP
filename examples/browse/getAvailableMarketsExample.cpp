//
// Created by Harry Skerritt on 22/12/2025.
//


#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will display all available markets

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);



    auto markets = client.browse().getAvailableMarkets();

    if (markets.has_value()) {
        std::cout << "   * Available Markets: " << markets->size() << " *   " << std::endl;
        std::cout << "--------------------------------" << std::endl;

        for (auto m : *markets) {
            std::cout << m << std::endl;
        }
    }


    return 0;
}
