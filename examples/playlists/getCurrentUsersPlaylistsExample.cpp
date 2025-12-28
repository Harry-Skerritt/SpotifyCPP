//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info the current users first 5 saved playlists


    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto user_playlists = client.playlist().getCurrentUsersPlaylists(5);

    if (user_playlists.has_value()) {
        std::cout << "\n\n  * Users Top: " << user_playlists->limit << " Playlists *  " << std::endl;
        std::cout << "-------------------------------" << std::endl;

        int i = 1;
        for (const auto& playlist : user_playlists->items) {
            std::cout << "\n\n Playlist: " << i << "/" << user_playlists->limit << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Playlist Name: " << playlist.name << std::endl;
            std::cout << "Owned by: " << playlist.owner.display_name.value_or("unknown") << std::endl;
            std::cout << "Track Count: " << playlist.tracks.total << std::endl;
            std::cout << "Cover Image: " << playlist.images.at(0).url << std::endl;
            i++;
        }
    }


    return 0;
}