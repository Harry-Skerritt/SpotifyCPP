//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will remove the input album from the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> audiobook_ids = {"2CuUBkbEhsiy67oAMl3MOE"};

    client.audiobook().removeUsersSavedAudiobooks(audiobook_ids);

    std::cout << "Removed Audiobook!" << std::endl;

    return 0;
}