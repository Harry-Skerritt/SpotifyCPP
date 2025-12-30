//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the currently available devices in the console

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto devices = client.player().getAvailableDevices();

    if (devices.devices.empty()) {
        std::cout << "No active Spotify devices found. Open Spotify on a device to see it here." << std::endl;
        return 0;
    }

    std::cout << "\n   * " << devices.devices.size() << " Available Devices *   " << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (const auto& device : devices.devices) {
        std::string activeStatus = device.is_active ? " (Active)" : "";
        std::cout << "- " << device.name << " [" << device.type << "]" << activeStatus << std::endl;
    }

    return 0;
}