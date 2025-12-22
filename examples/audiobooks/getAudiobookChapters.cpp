//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will display the chapters from an audiobook

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::string audiobook_id = "1sRuvLEIyo7AzyUiywE6Sb";
    auto audiobook_chapters = client.audiobook().getAudiobookChapters(audiobook_id);

    if (audiobook_chapters.has_value()) {
        std::cout << "\n\n   * Total Chapters *   " << std::endl;
        std::cout << "----------- " << audiobook_chapters->total << " -----------" << std::endl;

        for (auto chapter : audiobook_chapters->items) {
            std::cout << "\n\n Chapter: " << chapter.chapter_number << "/" << audiobook_chapters->total << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Chapter Name: " << chapter.name << std::endl;
        }
    }


    return 0;
}
