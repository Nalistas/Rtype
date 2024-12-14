/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

// #include <iostream>

// int main() {
//     // Vérifier la plateforme
//     #ifdef PLATFORM_WINDOWS
//         std::cout << "Running on Windows platform." << std::endl;
//     #elif defined(PLATFORM_LINUX)
//         std::cout << "Running on Linux platform." << std::endl;
//     #else
//         std::cout << "Unknown platform." << std::endl;
//     #endif
//     return 0;
// }

#include "Server.hpp"
#include "Thread/ThreadPool.hpp"
#include "SafeDirectoryLister.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"
#include <memory>

int main() {
    SafeDirectoryLister sd;
    sd.open(".", false);
    DLLdr::DLLoader<rtype::IGame> dll;

    dll.open("./libRtype.so");

    std::unique_ptr<rtype::IGame> game = dll.getSym("gameElement");

    Server server;
    server.loop();
    return 0;
}
