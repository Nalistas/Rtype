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


void TcpProtocol::changeStatus(std::shared_ptr<asio::ip::tcp::socket> &client)
{
    auto it = this->_clients.find(client);

    if (it == this->_clients.end() || it->second.getRoomId() == 0 || it->second.getName() == "") {
        std::cout << "Client not found or not in a room or does not have a name" << std::endl;
        _tcpServer.send(client, this->formatKo());
        return;
    }
    it->second.setReady(!it->second.isReady());
    _tcpServer.send(client, this->formatOk());
    std::cout << "Change Status client of " << client << std::endl;

    for (auto &clientIt : this->_clients) {
        if (clientIt.second.getRoomId() == it->second.getRoomId() && clientIt.second.isReady() == false) {
            std::cout << "Client " << clientIt.second.getName() << " not ready, cannot launch the game" << std::endl;
            return;
        }
    }
    this->_launchGame(it->second.getRoomId());
}

void TcpProtocol::setName(std::shared_ptr<asio::ip::tcp::socket> &client, std::string name)
{
    std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
    auto it = this->_clients.find(client);

    if (it != this->_clients.end() || it->second.getName() == "") {
        it->second.setName(name);
        std::cout << "Set name of " << client << " to " << name << std::endl;
        _tcpServer.send(client, data);
    } else {
        std::cout << "Client not found" << std::endl;
        data[0] = static_cast<uint8_t>(201);
        _tcpServer.send(client, data);
    }
}

void TcpProtocol::listRooms(std::shared_ptr<asio::ip::tcp::socket> &client)
{

    for (auto &room : _rooms) {
        std::vector<uint8_t> data = this->formatRoomCreatedDeleted(room.first, true);
        _tcpServer.send(client, data);
    }
}

void TcpProtocol::enterRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId)
{
    auto roomIt = this->_rooms.find(roomId);
    auto clientIt = this->_clients.find(client);

    if (roomIt == this->_rooms.end() || clientIt == this->_clients.end() || clientIt->second.getName() == "") {
        _tcpServer.send(client, this->formatKo());
        std::cout << "Client " << client << " error when entering the room " << roomId << std::endl;
        return;
    }
    this->_clients[client].setRoomId(roomId);
    _tcpServer.send(client, this->formatOk());
    std::cout << "Client " << clientIt->second.getName() << " entered room " << roomId << std::endl; 

    auto data = this->formatPlayerRoomUpdate(roomId, true, clientIt->second.getName());
    for (auto &sclient : this->_clients) {
        _tcpServer.send(sclient.first, data);
    }
}

void TcpProtocol::exitRoom(std::shared_ptr<asio::ip::tcp::socket> &client)
{
    auto clientIt = this->_clients.find(client);
    uint8_t roomId = this->_clients[client].getRoomId();
    auto roomIt = this->_rooms.find(roomId);

    if (clientIt == this->_clients.end() || clientIt->second.getRoomId() == 0 || clientIt->second.getName() == "") {
        _tcpServer.send(client, this->formatKo());
        std::cout << "Client " << client << " not found, already in lobby or does not have a name, room not exited" << std::endl;
        return;
    }

    clientIt->second.setReady(false);
    clientIt->second.setRoomId(0);
    _tcpServer.send(client, this->formatOk());
    std::cout << "Client " << clientIt->second.getName() << " exited room " << roomId << std::endl;

    if (roomIt == this->_rooms.end()) {
        std::cout << "Room " << roomId << " not found" << std::endl;
        return;
    }

    auto next_client_in_room = isRoomEmpty(roomId);
    if (next_client_in_room == nullptr) {
        return deleteRoom(client, roomId);
    }
    if (roomIt->second.getOwner() == client) {
        roomIt->second.setOwner(next_client_in_room);
    }
    auto data = this->formatPlayerRoomUpdate(roomId, false, clientIt->second.getName());
    for (auto &clientIt : this->_clients) {
        _tcpServer.send(clientIt.first, data);
    }
}

void TcpProtocol::createRoom(std::shared_ptr<asio::ip::tcp::socket> &client, std::string roomName, std::string gameName)
{
    uint8_t roomId = 1;
    auto client_it = this->_clients.find(client);

    if (client_it == this->_clients.end() || client_it->second.getName() == "") {
        _tcpServer.send(client, this->formatKo());
        std::cout << "Client not found or doesn't have a name" << std::endl;
        return;
    }

    for (uint8_t i = 1; i < 255; i++) {
        if (this->_rooms.find(i) == this->_rooms.end()) {
            roomId = i;
            break;
        }
    }
    if (this->_rooms.find(roomId) != this->_rooms.end()) {
        _tcpServer.send(client, this->formatKo());
        std::cout << "Too many rooms" << std::endl;
        return;
    }
    this->_rooms.emplace(roomId, Room(roomName, gameName, client));
    client_it->second.setRoomId(roomId);
    _tcpServer.send(client, this->formatOk());
    std::vector<uint8_t> data = this->formatRoomCreatedDeleted(roomId, true);
    std::cout << "Room " << roomId << " created, broadcasting" << std::endl;

    for (auto clientIt : this->_clients) {
        if (clientIt.second.getRoomId() == 0) {
            _tcpServer.send(clientIt.first, data);
        }
    }
    return;
}





void TcpProtocol::deleteRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId)
{
    auto it = this->_rooms.find(roomId);

    if (it != this->_rooms.end() && it->second.getOwner() == client) {
        for (auto clientIt : this->_clients) {
            this->_tcpServer.send(clientIt.first, {1, 2, it->first});
            if (clientIt.second.getRoomId() == roomId) {
                clientIt.second.setRoomId(0);
            }
        }
        this->_rooms.erase(it);
        std::cout << "Room " << roomId << " deleted" << std::endl;
    } else {
        if (it == this->_rooms.end()) {
            std::cout << "Room " << roomId << " not found" << std::endl;
        } else {
            std::cout << "Room " << roomId << " not deleted : not owner" << std::endl;
        }
    }
}
