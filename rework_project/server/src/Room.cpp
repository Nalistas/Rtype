/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ROOM
*/

#include "Room.hpp"

Room::Room(std::string const &name, std::string const &gameName, std::shared_ptr<asio::ip::tcp::socket> &owner) :
    _name(name), _gameName(gameName), _owner(owner)
{
}

Room::~Room()
{}

std::shared_ptr<asio::ip::tcp::socket> const &Room::getOwner() const
{
    return _owner;
}

std::string const &Room::getName() const
{
    return _name;
}

std::string const &Room::getGameName() const
{
    return _gameName;
}

void Room::setName(std::string const &name)
{
    _name = name;
}

void Room::setGameName(std::string const &gameName)
{
    _gameName = gameName;
}

void Room::setOwner(std::shared_ptr<asio::ip::tcp::socket> &owner)
{
    _owner = owner;
}
