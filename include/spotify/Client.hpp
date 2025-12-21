//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "Auth.hpp"


namespace Spotify {
    class Client {
        // Funcs
    public:
        Client();
        ~Client() = default;

    private:

    // Vars
    public:

    private:

        Auth* auth;

    };

}



#endif //CLIENT_H
