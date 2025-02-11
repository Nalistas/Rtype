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
    (void)roomId;
    return {static_cast<uint8_t>(INSTRUCTIONS_SERVER_TO_CLIENT::START_GAME)};
}

std::vector<uint8_t> TcpProtocol::formatRoomCreatedDeleted(uint8_t roomId, bool created)
{
    auto room = _rooms.find(roomId);
    std::string const &room_name = room->second.getName();
    std::string const &game_name = room->second.getGameName();
    std::size_t size = 5 + room_name.size() + game_name.size();
    std::cout << "Room name size : " << size << std::endl;
    std::vector<uint8_t> data(size);

    data[0] = static_cast<uint8_t>(INSTRUCTIONS_SERVER_TO_CLIENT::ROOM_UPDATE);
    data[1] = created;
    data[2] = roomId;
    data[3] = 0;
    std::copy(room_name.begin(), room_name.end(), data.begin() + 4);
    data[room_name.size() + 4] = 0;
    std::copy(game_name.begin(), game_name.end(), data.begin() + 5 + room_name.size());

    for (auto &client : _clients) {
        if (client.second.getRoomId() == roomId) {
            ++data[3];
        }
    }
    return data;
}

std::vector<uint8_t> TcpProtocol::formatGameAvailable(uint8_t roomId)
{
    (void)roomId;
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

std::vector<uint8_t> TcpProtocol::formatForceRegisterInRoom(uint8_t roomId)
{
    auto room_it = _rooms.find(roomId);

    std::cout << "Force register in room" << std::endl;
    if (room_it == _rooms.end()) {
        return {FORCE_REGISTER_IN_ROOM, roomId, 0};
    }
    std::vector<uint8_t> data(2 + room_it->second.getName().size());
    data[0] = FORCE_REGISTER_IN_ROOM;
    data[1] = roomId;
    std::copy(room_it->second.getName().begin(), room_it->second.getName().end(), data.begin() + 2);
    return data;
}
