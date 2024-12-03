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

int main() {
    // Server server;
    // server.loop();

    thread::ThreadPool<std::function<int()>, int> pool(4);

    pool.run();

    pool.addTask([]() {
        std::cout << "Hello, world!" << std::endl;
        return 0;
    });
    pool.waitUntilComplete();
    return 0;
}
