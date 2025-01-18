/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/

#include "ServerLauncher.hpp"
#include "RoomsCore.hpp"

ServerLauncher::ServerLauncher()
{
}

ServerLauncher::~ServerLauncher()
{
}

void ServerLauncher::LaunchUdpServer(std::string const &port, std::string const &gameName)
{
    (void)port;
    (void)gameName;
}

void ServerLauncher::LaunchTcpServer(std::string const &port)
{
    RoomsCore core(port);
    core.run();
}