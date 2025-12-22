//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single audiobook from an id, and multiple audiobooks from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Single Audiobook
    std::string audiobook_id = "1yPC9bBMm1fixXasXnTRGH";
    auto single_audiobook = client.audiobook().getAudiobook(audiobook_id);

    if (single_audiobook.has_value()) {
        std::cout << "     * Single Audiobook *      " << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cout << single_audiobook->name << " by " << single_audiobook->authors.at(0).name << std::endl;

        std::cout << "Narrated by: " << std::endl;
        for (auto narrator : single_audiobook->narrators) {
            std::cout << "- " << narrator.name << std::endl;
        }

        std::cout << "Chapter Count: " << single_audiobook->total_chapters << std::endl;
    }

    // Multi Audiobook
    std::vector<std::string> audiobook_ids { "6YbAa0Qkhxay23rWNLNyZE", "1sRuvLEIyo7AzyUiywE6Sb" };
    auto multi_audiobooks = client.audiobook().getMultipleAudiobooks(audiobook_ids);

    if (multi_audiobooks.has_value()) {
        std::cout << "\n\n      * Multi Audiobook *      " << std::endl;
        std::cout << "-------------------------------" << std::endl;

        int i = 1;
        for (auto audiobook : multi_audiobooks->audiobooks) {
            std::cout << "\n\n Book: " << i << "/" << multi_audiobooks->audiobooks.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << audiobook.name << " by " << audiobook.authors.at(0).name << std::endl;

            std::cout << "Narrated by: " << std::endl;
            for (auto narrator : audiobook.narrators) {
                std::cout << "- " << narrator.name << std::endl;
            }

            std::cout << "Chapter Count: " << audiobook.total_chapters << std::endl;
            i++;
        }
    } else { std::cout << "No Audiobooks!" << std::endl; }


    return 0;
}
