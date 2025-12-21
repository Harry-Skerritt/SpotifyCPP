//
// Created by Harry Skerritt on 21/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>

int main () {
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto devices = client.player().getAvailableDevices();

    if (!devices.has_value()) {
        std::cerr << "No player found!" << std::endl;
        return 1;
    }

    std::cout << "There are " << devices->devices.size() << " available devices" << std::endl;

    for (const auto& device : devices->devices) {
        std::cout << device.name << std::endl;
    }


    auto queue = client.player().getUsersQueue();

    if (!queue.has_value()) {
        std::cerr << "No users found!" << std::endl;
        return 1;
    }

    std::cout << "There are " << queue->queue.size() << " item(s) in queue" << std::endl;


}