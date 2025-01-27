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


int main(int ac, char **av)
{
    std::vector<std::string> args(ac);
    ServerLauncher launcher(av[0]);

    for (int i = 0; i < ac; ++i) {
        args[i] = std::string(av[i]);
    }
    std::cout << "args size : " << args.size() << std::endl;
    for (auto &arg : args) {
        std::cout << arg << std::endl;
    }
    if (args.size() > 4) {
        std::cerr << "Error : invalid number of argument" << std::endl;
        return 84;
    }
    if (args.size() == 4) {
        std::string port_string = args[2];
        std::string gameName = args[3];
        uint16_t port;
        try {
            port = std::stoi(port_string);
        } catch (const std::exception &e) {
            std::cerr << "Error :" << e.what() << std::endl;
            return 84;
        }
        if (args[1] == "-udp") {
            std::cout << "++++++++++++++++++++++++++++++" << std::endl;
            std::cout << "UDP" << std::endl;
            launcher.LaunchUdpServer(port_string, gameName);
        }
    } else if (args.size() <= 2) {
        std::string port_string = args.size() == 2 ? args[1] : "2000";
        uint16_t port;
        try {
            port = std::stoi(port_string);
            launcher.LaunchTcpServer(port_string);
        } catch (const std::exception &e) {
            std::cerr << "Error :" << e.what() << std::endl;
            return 84;
        }
    }

    return 0;
}
