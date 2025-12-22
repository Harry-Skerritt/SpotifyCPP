//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will show the results of searching for a query with selected types

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    std::string search_query = "Iron Maiden";
    std::vector<Spotify::SearchType> search_types = { Spotify::SearchType::Artist, Spotify::SearchType::Track, Spotify::SearchType::Album };

    auto search = client.browse().searchForItem(search_query, search_types, "GB");

    if (search.has_value()) {
        if (search->artists.has_value()) {
            auto artists = search->artists.value();
            std::cout << "\n\n * Search Results: Artists * " << std::endl;
            std::cout << "---- Found: " << artists.items.size() << " results ----" << std::endl;

            int i = 0;
            for (auto& a : artists.items) {
                std::cout << i++ << ". Artist Name: " << a.name << std::endl;
            }
        } else {
            std::cout << "\n\nNo artists found!" << std::endl;
        }

        if (search->albums.has_value()) {
            auto albums = search->albums.value();
            std::cout << "\n\n * Search Results: Albums * " << std::endl;
            std::cout << "---- Found: " << albums.items.size() << " results ----" << std::endl;

            int i = 0;
            for (auto& a : albums.items) {
                std::cout << i++ << ". Album Title: " << a.name << std::endl;
            }
        } else {
            std::cout << "\n\nNo albums found!" << std::endl;
        }

        if (search->tracks.has_value()) {
            auto tracks = search->tracks.value();
            std::cout << "\n\n * Search Results: Tracks * " << std::endl;
            std::cout << "---- Found: " << tracks.items.size() << " results ----" << std::endl;

            int i = 0;
            for (auto& t : tracks.items) {
                std::cout << i++ << ". Track Title: " << t.name << std::endl;
            }
        } else {
            std::cout << "\n\nNo tracks found!" << std::endl;
        }

        if (!search->playlists.has_value()) {
            std::cout << "\n\nNo playlists found!" << std::endl;
        }
    }


    return 0;
}
