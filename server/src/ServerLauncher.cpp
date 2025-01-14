/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/

#include "ServerLauncher.hpp"
#include "RoomCore.hpp"

ServerLauncher::ServerLauncher()
{
}

ServerLauncher::~ServerLauncher()
{
}

void ServerLauncher::LaunchUdpServer(std::string const &port)
{
}

void ServerLauncher::LaunchTcpServer(std::string const &port)
{
    RoomCore core(port);
    core.run();
}