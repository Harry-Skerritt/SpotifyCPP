//
// Created by Harry Skerritt on 28/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the href link to the playlist covers
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    std::string playlist_id = "37i9dQZEVXbmL4XmQSFR2v";
    auto cover_data = client.playlist().getPlaylistCoverImage(playlist_id);

    if (cover_data.has_value()) {
        for (auto& cover : cover_data.value()) {
            std::cout << cover.height.value_or(0) << "x" << cover.width.value_or(0) << ": " << cover.url << std::endl;
        }
    }







    return 0;
}