//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will save the input album to the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> audiobook_ids = {"2CuUBkbEhsiy67oAMl3MOE"};

    client.audiobook().saveAudiobookForUser(audiobook_ids);

    std::cout << "Saved Audiobook!" << std::endl;

    return 0;
}