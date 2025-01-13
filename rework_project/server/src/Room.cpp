/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ROOM
*/

#include "Room.hpp"

Room::Room(std::string name, std::string gameName, int id) : _name(name), _gameName(gameName), _id(id)
{
}

Room::~Room()
{}

void Room::addClient(std::shared_ptr<asio::ip::tcp::socket> client)
{
    _clients.push_back(std::make_pair(client, false));
}

void Room::removeClient(std::shared_ptr<asio::ip::tcp::socket> client)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->first == client) {
            _clients.erase(it);
            return;
        }
    }
}

bool Room::isClientInRoom(std::shared_ptr<asio::ip::tcp::socket> client)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->first == client) {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<std::shared_ptr<asio::ip::tcp::socket>, bool>> Room::getClients()
{
    return _clients;
}

std::string Room::getName()
{
    return _name;
}

std::string Room::getGameName()
{
    return _gameName;
}

int Room::getId()
{
    return _id;
}

void Room::setName(std::string const &name)
{
    _name = name;
}

bool Room::isEveryoneReady()
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (!it->second) {
            return false;
        }
    }
    return true;
}

void Room::changeClientStatus(std::shared_ptr<asio::ip::tcp::socket> client)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->first == client) {
            it->second = !it->second;
            return;
        }
    }
}

int Room::getNbClients()
{
    return _clients.size();
}
