/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ROOM
*/

#include "ClientRoom.hpp"

ClientRoom::ClientRoom(std::string const &name, uint8_t id, int nbPlayers)
    : _name(name), _id(id), _nbPlayers(nbPlayers)
{
}

ClientRoom::~ClientRoom()
{}

std::string const &ClientRoom::getName() const
{
    return _name;
}

uint8_t ClientRoom::getId() const
{
    return _id;
}

int ClientRoom::getNbPlayers() const
{
    return _nbPlayers;
}

void ClientRoom::setNbPlayers(int nbPlayers)
{
    _nbPlayers = nbPlayers;
}

void ClientRoom::setGameName(std::string gameName)
{
    _gameName = gameName;
}

std::string ClientRoom::getGameName() const
{
    return _gameName;
}
