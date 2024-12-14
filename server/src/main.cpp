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
#include <memory>

int main() {
    Server server;
    server.loop();
    return 0;
}
