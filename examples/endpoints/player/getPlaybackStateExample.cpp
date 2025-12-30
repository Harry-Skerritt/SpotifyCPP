//
// Created by Harry Skerritt on 22/12/2025.
//
//
// Created by Harry Skerritt on 21/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>


int main () {

    // This will show the current state of playback

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto state = client.player().getPlaybackState();


    if (!state.has_value()) {
        std::cout << "Nothing is playing (or private session is active)." << std::endl;
        return 0;
    }

    std::cout << "\n\n      * Playback State *      " << std::endl;
    std::cout << "------------------------------" << std::endl;

    std::cout << "Current Device: " << state->device.name << std::endl;
    std::cout << "Current Track href: " << state->context.href << std::endl;
    std::cout << "Current Track is: " << state->asTrack()->name << " by " << state->asTrack()->artists.at(0).name << std::endl;

    return 0;
}