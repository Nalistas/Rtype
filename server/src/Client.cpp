/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() :
    _room_id(0),
    _name(""),
    _ready(false)
{
}

Client::~Client()
{
}

uint8_t Client::getRoomId() const
{
    return _room_id;
}

void Client::setRoomId(uint8_t roomId)
{
    _room_id = roomId;
}

std::string Client::getName() const
{
    return _name;
}

void Client::setName(std::string name)
{
    _name = name;
}

bool Client::isReady() const
{
    return _ready;
}

void Client::setReady(bool ready)
{
    _ready = ready;
}
