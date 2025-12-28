//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a playlist in the console

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // 5uRs8PvITxHLwxW2JQ34cg
    std::string playlist_id = "3cEYpjA9oz9GiPac4AsH4n";
    auto playlist_data = client.playlist().getPlaylist(playlist_id);

    if (playlist_data.has_value()) {
        std::cout << "\n\n * " << playlist_data->name << " * " << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Desc: " << playlist_data->description.value_or("none") << std::endl;
        std::cout << "Owned By: " << playlist_data->owner.display_name.value_or("unknown") << std::endl;
        std::cout << "Playlist Cover: " << playlist_data->images.at(0).url << std::endl;
        std::cout << "Track Count: " << playlist_data->tracks.total << std::endl;

        int to_show = 5;
        for (int i = 0; i < to_show; i++) {
            auto& item = playlist_data->tracks.items[i];

            std::cout << "\nTrack " << (i+1) << "/" << to_show << std::endl;

            if (auto track = item.asTrack()) {
                std::cout << track->name << " - " << track->artists.at(0).name << std::endl;
            }
            else if (auto episode = item.asEpisode()) {
                std::cout << "[Episode] " << episode->name << std::endl;
            }
            else {
                std::cout << "Unknown Playable Type" << std::endl;
            }
        }


    }





    return 0;
}