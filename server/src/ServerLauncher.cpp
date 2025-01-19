/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/

#include "ServerLauncher.hpp"
#include "GameLauncher.hpp"
#include "RoomsCore.hpp"

ServerLauncher::ServerLauncher()
{
}

ServerLauncher::~ServerLauncher()
{
}

void ServerLauncher::LaunchUdpServer(std::string const &port, std::string const &gameName)
{
    GameLauncher core(gameName, std::stoi(port));
    // GameLauncher core(gameName, gameport);
    core.launch();
}

void ServerLauncher::LaunchTcpServer(std::string const &port)
{
    RoomsCore core(port);
    core.run();
}