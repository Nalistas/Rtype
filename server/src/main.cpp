/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include <iostream>
#include <string>
#include <vector>
#include "RoomsCore.hpp"
#include "registry.hpp"
#include "isystem.hpp"
#include "GameLauncher.hpp"
#include "ServerLauncher.hpp"
#include "Process.hpp"

struct speed {
    int x;
    int y;
};

struct position {
    int x;
    int y;
};

class MovementSystem : public ecs::isystem<speed, position> {
    public:
        MovementSystem() = default;
        ~MovementSystem() = default;

        void operator()(ecs::registry &registry, sparse_array<speed> &speeds, sparse_array<position> &positions) override {
            (void)registry;
            for (auto [index, speed, position] : zipper(speeds, positions)) {
                std::cout << "coucou " << index << std::endl;
            }
        }
};

class NoneSystem : public ecs::isystem<> {
    public:
        NoneSystem() = default;
        ~NoneSystem() = default;
    
        void operator()(ecs::registry &registry) override
        {
            (void)registry;
            std::cout << "NoneSystem" << std::endl;
        }
};

int main(int ac, char **av)
{
    if (ac != 1) {
        std::cout << "OTHER PROCESS !!!" << std::endl;
        while (1) {
            std::cout << "COUCOU HUGO, JE VAIS MANGER !!! A DEMAIN" << std::endl;
        }
        return 0;
    }
    process::Process my_process;
    std::vector<std::string> vec = {"./build/r-type_server.exe", "coucou"};
    my_process.execProcess(vec);
    Sleep(5000);

    return 0;
    std::vector<std::string> args(ac);
    ServerLauncher launcher;

    for (int i = 0; i < ac; ++i) {
        args[i] = std::string(av[i]);
    }
    if (args.size() > 3) {
        std::cerr << "Error : invalid number of argument" << std::endl;
        return 84;
    }

    if (args.size() == 3) {
        std::string port_string = args[2];
        uint16_t port;
        try {
            port = std::stoi(port_string);
        } catch (const std::exception &e) {
            std::cerr << "Error :" << e.what() << std::endl;
            return 84;
        }
        if (args[1] == "udp") {
            launcher.LaunchUdpServer(port_string);
        }
    } else if (args.size() <= 2) {
        std::string port_string = args.size() == 2 ? args[1] : "1024";
        uint16_t port;
        try {
            port = std::stoi(port_string);
        } catch (const std::exception &e) {
            std::cerr << "Error :" << e.what() << std::endl;
            return 84;
        }
        launcher.LaunchTcpServer(port_string);
    }

    // GameLauncher launcher("./libr-type.so");
    // std::list<GameLauncher::Player> players = {{"player1", "127.0.0.1"}, {"player2", "127.0.0.1"}, {"player3", "127.0.0.1"}};
    // launcher.launch(players);

    // RoomsCore core("12345");
    // core.run();

/*
    ecs::registry registry;

    // RoomsCore core("12345");
    // core.run();
    */
    return 0;
}
