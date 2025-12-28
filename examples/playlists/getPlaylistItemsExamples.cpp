//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will display the track listing of an playlist, from the playlist id
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::string playlist_id = "3cEYpjA9oz9GiPac4AsH4n";
    auto playlist_data = client.playlist().getPlaylistItems(playlist_id);

    if (playlist_data.has_value()) {
        std::cout << "\n\n     * Total Items *     " << std::endl;
        std::cout << "----------- " << playlist_data->total << " -----------" << std::endl;

        int i = 1;
        for (auto item : playlist_data->items) {
            auto track = item.asTrack();
            std::cout << "\n\n Track: " << i << "/" << playlist_data->total << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Song Name: " << track->name << std::endl;
            std::cout << "Artist: " << track->artists.at(0).name << std::endl;
            std::cout << "Is Explicit: " << track->is_explicit << std::endl;
            std::cout << "Track ID: " << track->uri << std::endl;
            i++;
        }
    }


    return 0;
}