//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about the top X (5 in this case) of the users saved albums

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto user_audiobooks = client.audiobook().getUsersSavedAudiobooks(5);

    if (user_audiobooks.has_value()) {
        std::cout << "\n\n  * Users Top: " << user_audiobooks->limit << " Audiobooks *  " << std::endl;
        std::cout << "----------------------------" << std::endl;

        int i = 1;
        for (const auto& saved_book : user_audiobooks->items) {
            std::cout << "\n\n Audiobook: " << i << "/" << user_audiobooks->items.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << saved_book.name << " by " << saved_book.authors.at(0).name << std::endl;
            std::cout << "Edition: " << saved_book.edition << std::endl;
            std::cout << "Chapter Count: " << saved_book.total_chapters << std::endl;
            i++;
        }
    }


    return 0;
}