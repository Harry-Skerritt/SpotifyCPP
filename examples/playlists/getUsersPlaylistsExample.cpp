//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info an input users first 5 saved playlists
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // Todo: Change this ID before release
    std::string user_id = "q9yloghaebslto83wa1r4yqv5";
    auto user_playlists = client.playlist().getUsersPlaylists(user_id, 5);

    if (user_playlists.has_value()) {
        std::string display_name = user_playlists->items.at(0).owner.display_name.value_or("unknown");
        std::cout << "\n\n  * " << display_name<< " Top: " << user_playlists->limit << " Playlists *  " << std::endl;
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