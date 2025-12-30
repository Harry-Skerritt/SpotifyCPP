//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will print the users queue to the console

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto queue = client.player().getUsersQueue();

    if (queue.queue.empty()) {
        std::cerr << "Error getting queue - returned empty!" << std::endl;
        return 0;
    }


    std::cout << "\n\n       * Users Queue *       " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << queue.queue.size() << " item(s) in queue" << std::endl;

    int i = 1;
    for (const auto& queue_obj : queue.queue) {
        if (auto track = queue_obj.asTrack()) {
            std::cout << "\n\n   * Queue Track: " << i << "/" << queue.queue.size() << " *   " << std::endl;
            std::cout << "----------------------------" << std::endl;
            std::cout << "Track Title: " << track->name << std::endl;
            std::cout << "Track Artist: " << track->artists.at(0).name << std::endl;
            std::cout << "Track Length: " << track->duration_ms << "ms" << std::endl;
        }
        else if (auto episode = queue_obj.asEpisode()) {
            std::cout << "\n\n   * Queue Track: " << i << "/" << queue.queue.size() << " *   " << std::endl;
            std::cout << "Show: " << episode->show.name << std::endl;
            std::cout << "Show Publisher: " << episode->show.publisher << std::endl;
        }

        i++;
    }

    return 0;




}