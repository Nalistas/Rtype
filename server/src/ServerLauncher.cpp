/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/

#include "ServerLauncher.hpp"
#include "GameLauncher.hpp"
#include "RoomsCore.hpp"

ServerLauncher::ServerLauncher(std::string const &executable_name) :
    _executable_name(executable_name)
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
    RoomsCore core(_executable_name, port);
    core.run();
}