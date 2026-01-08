//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"
#include "../../../include/spotify/util/parse/SpotifyParser.hpp"

int main () {

    // This will display info about a single album from an id, and multiple albums from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Single Album

    std::string album_id = Spotify::Parse::extractID("https://open.spotify.com/album/2SV07gBGZm6kE8yS5XohLL?si=EL_3A49DTt2ZNX4vtWUbZQ");
    auto single_album = client.album().getAlbum(album_id);


    std::cout << "     * Single Album *      " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << single_album.name << " by " << single_album.artists.at(0).name << std::endl;
    std::cout << "Released: " << single_album.release_date << std::endl;
    std::cout << "Track Count: " << single_album.total_tracks << std::endl;
    std::cout << "Album Popularity: " << single_album.popularity << std::endl;

    for (auto& img : single_album.images) {
        std::cout <<"(" << img.width.value_or(0) << "x" << img.height.value_or(0) << "): " << img.url << std::endl;
    }

    // Multi Album
    std::vector<std::string> album_urls {
        "https://open.spotify.com/album/6TZp52tXShLQbq8yNMxqNT?si=NFZf8rVTTYa724KzZi6N4g",
        "https://open.spotify.com/album/3kB4VjXKKCY7l5xeH113Da?si=10a580278fb549ec",
        "https://open.spotify.com/album/3YhgdRfaZrVIOORGK9SNiV?si=238d67a1f0c044c6"
    };
    auto multi_albums = client.album().getMultipleAlbums(Spotify::Parse::extractIDs(album_urls));

    std::cout << "\n\n      * Multi Album *      " << std::endl;
    std::cout << "---------------------------" << std::endl;

    int i = 1;
    for (auto album : multi_albums.albums) {
        std::cout << "\n\n Album: " << i << "/" << multi_albums.albums.size() << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << album.name << " by " << album.artists.at(0).name << std::endl;
        std::cout << "Released: " << album.release_date << std::endl;
        std::cout << "Track Count: " << album.total_tracks << std::endl;
        std::cout << "Album Popularity: " << album.popularity << std::endl;
        i++;
    }


    return 0;
}
