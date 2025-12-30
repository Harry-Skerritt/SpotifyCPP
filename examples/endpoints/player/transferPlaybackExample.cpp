//
// Created by Harry Skerritt on 22/12/2025.
//


#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>

int main () {

    // This will output possible devices and then ask the user which one theyd like to transfer too

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Output Current Devices
    auto devices = client.player().getAvailableDevices();

    if (devices.devices.empty()) {
        std::cout << "No active Spotify devices found. Open Spotify on a device to see it here." << std::endl;
        return 0;
    }


    std::cout << "   * " << devices.devices.size() << " Available Devices *   " << std::endl;
    std::cout << "-----------------------------" << std::endl;

    int i = 1;
    for (const auto& device : devices.devices) {
        std::cout << i << ": " << device.name << std::endl;
        i++;
    }

    // Get user input
    std::cout << "Enter device number: ";
    std::string entered_device;
    std::getline(std::cin, entered_device);

    // Get the id of the device
    int device_number = std::stoi(entered_device) - 1;
    auto device_id = devices.devices.at(device_number).id;

    std::vector id_to_send = {device_id.value_or("")};

    // Transfer playback
    client.player().transferPlayback(id_to_send, true);


    return 0;
}