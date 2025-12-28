//
// Created by Harry Skerritt on 28/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will create a playlist, add items to it, change the title and then remove everything - tests multiple endpoints

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Creating the playlist
    // Todo: Make it get the users id once that API is implenented
    auto new_playlist = client.playlist().createPlaylist(
        "discodudde","Test Playlist", true, false, "A test playlist made with SpotifyAPILib");

    std::string playlist_id;
    if (new_playlist.has_value()) {
        std::cout << "Created playlist: " << new_playlist->name << std::endl;
        playlist_id = new_playlist->id;
    } else {
        std::cout << "No playlist found" << std::endl;
    }

    // Change Cover Image

    // Add items
    std::vector<std::string> uris_to_add ={
        "spotify:track:5FVd6KXrgO9B3JPmC8OPst",
        "spotify:track:3CWIBLKz5S0nTCTP2fXqJN",
        "spotify:track:7LdTC8ChOM1NZhY5pUhDZ9",
        "spotify:track:7cUHFTxJhxtZ5tpY34SMRw",
        "spotify:track:7kwoZQIJGWeY4dALynwf2l"
    };
    client.playlist().addItemsToPlaylist(playlist_id, uris_to_add);
    std::cout << "Added items to playlist!" << std::endl;


    // Change playlist name
    std::cout << "\nEnter new name for playlist: ";
    std::string new_playlist_name;
    std::getline(std::cin, new_playlist_name);

    client.playlist().changePlaylistDetails(playlist_id, new_playlist_name);
    std::cout<< "Changed playlist name to: " << new_playlist_name << std::endl;

    // Reorder playlist
    client.playlist().reorderPlaylistItems(playlist_id, 1, 3, 2);


    // Remove one item
    std::cout << "\nType anything to remove one item: ";
    std::string remove_item_query;
    std::getline(std::cin, remove_item_query);

    std::vector<Spotify::URIObject> uris_to_remove = { {"spotify:track:3CWIBLKz5S0nTCTP2fXqJN"} };
    client.playlist().removePlaylistItems(playlist_id, uris_to_remove);
    std::cout << "Removed item from playlist!" << std::endl;



    // Wait for user to remove playlist
    std::cout << "\nType 'Y' to remove playlist: ";
    std::string remove_query;
    std::getline(std::cin, remove_query);
    std::transform(remove_query.begin(), remove_query.end(), remove_query.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if (remove_query != "y") {
        std::cout << "Playlist not removed!" << std::endl;
        return 0;
    }

    // Todo: From the user api so add when relevant
    std::cout << "Todo: From the user api so add when relevant" << std::endl;

    return 0;
}
