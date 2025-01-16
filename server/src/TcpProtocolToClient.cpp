/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TcpProtocol
*/

#include "TcpProtocol.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

std::vector<uint8_t> TcpProtocol::formatLaunchRoom(uint8_t roomId)
{
    return {static_cast<uint8_t>(INSTRUCTIONS_SERVER_TO_CLIENT::START_GAME)};
}

std::vector<uint8_t> TcpProtocol::formatRoomCreatedDeleted(uint8_t roomId, bool created)
{
    auto room = _rooms.find(roomId);
    std::size_t size = 5 + room->second.getName().size();
    std::vector<uint8_t> data(size);
    uint8_t nbPlayers = 0;

    data[0] = static_cast<uint8_t>(INSTRUCTIONS_SERVER_TO_CLIENT::ROOM_UPDATE);
    data[1] = created;
    data[2] = roomId;
    std::copy(room->second.getName().begin(), room->second.getName().end(), data.begin() + 3);
    data[size - 2] = '\\';

    for (auto &client : _clients) {
        if (client.second.getRoomId() == roomId) {
            ++nbPlayers;
        }
    }
    data[size - 1] = nbPlayers;
    return data;
}

std::vector<uint8_t> TcpProtocol::formatGameAvailable(uint8_t roomId)
{
    return {};
}

std::vector<uint8_t> TcpProtocol::formatPlayerRoomUpdate(uint8_t roomId, bool enter, std::string const &name)
{
    std::size_t size = 3 + name.size();
    std::vector<uint8_t> data(size);

    data[0] = static_cast<uint8_t>(INSTRUCTIONS_SERVER_TO_CLIENT::LEAVE_ENTER_ROOM);
    data[1] = enter;
    data[2] = roomId;
    std::copy(name.begin(), name.end(), data.begin() + 3);
    return data;
}

std::vector<uint8_t> TcpProtocol::formatKo(void)
{
    return {static_cast<uint8_t>(201)};
}

std::vector<uint8_t> TcpProtocol::formatOk(void)
{
    return {static_cast<uint8_t>(200)};
}
