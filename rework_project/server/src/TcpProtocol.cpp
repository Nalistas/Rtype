/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TcpProtocol
*/

#include "TcpProtocol.hpp"
#include <sstream>


TcpProtocol::TcpProtocol(TcpServer &server) : _tcpServer(server)
{
    _commandMap[1] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Set name
        std::string name;
        params >> name;
        _tcpServer._clients[client] = name;
        std::cout << "Set " << _tcpServer._clients[client] << " name\n";
        std::vector<char> data = {static_cast<char>(200)};
        _tcpServer.send(client, data);
    };
    _commandMap[2] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Enter room
        int roomId;
        params >> roomId;
        enterRoom(client, roomId);
        std::cout << "Enter room\n";
    };
    _commandMap[4] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Exit room
        exitRoom(client);
        std::cout << "Exit room\n";
    };
    _commandMap[7] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Create room
        std::string roomName;
        std::string gameName;
        params >> roomName >> gameName;
        createRoom(client, roomName, gameName);
        std::cout << "Create room\n";
    };
    _commandMap[8] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // List rooms
        listRooms(client);
        std::cout << "List rooms\n";
        std::vector<char> data = {static_cast<char>(200)};
        _tcpServer.send(client, data);
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data)
{
    std::istringstream stream(std::string(data.begin(), data.end()));
    char commandId;
    stream >> commandId;

    if (_commandMap.find(commandId) != _commandMap.end()) {
        _commandMap[commandId](client, stream);
    } else {
        std::cout << "Command not founded\n";
        std::vector<char> data = {static_cast<char>(201)};
        _tcpServer.send(client, data);
    }
}

void TcpProtocol::listRooms(std::shared_ptr<asio::ip::tcp::socket> client)
{
    std::vector<char> allData;

    for (auto &room : _tcpServer._rooms) {
        allData.push_back(room.getId());
        const std::string& roomName = room.getName();
        allData.insert(allData.end(), roomName.begin(), roomName.end());
        allData.push_back('\\');
        int personCount = room.getNbClients();
        allData.push_back(static_cast<char>(personCount));
        allData.push_back('#');
    }
    _tcpServer.send(client, allData);
}

void TcpProtocol::enterRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId)
{
    for (auto &otherRoom : _tcpServer._rooms) {
        if (otherRoom.getId() == roomId) {
            for (auto &room : _tcpServer._rooms) {
                if (room.isClientInRoom(client)) {
                    room.removeClient(client);
                }
            }
            otherRoom.addClient(client);
            std::vector<char> data = {static_cast<char>(200)};
            _tcpServer.send(client, data);
            return;
        }
    }
}

void TcpProtocol::exitRoom(std::shared_ptr<asio::ip::tcp::socket> client)
{
    for (auto &room : _tcpServer._rooms) {
        if (room.isClientInRoom(client)) {
            room.removeClient(client);
            for (auto &otherRoom : _tcpServer._rooms) {
                if (otherRoom.getName() == "lobby") {
                    otherRoom.addClient(client);
                }
            }
            std::vector<char> data = {static_cast<char>(200)};
            _tcpServer.send(client, data);
            return;
        }
    }
}

void TcpProtocol::createRoom(std::shared_ptr<asio::ip::tcp::socket> client, std::string roomName, std::string gameName)
{
    Room newRoom(roomName, gameName, _tcpServer._rooms.size());
    newRoom.addClient(client);
    _tcpServer._rooms.push_back(newRoom);
    std::vector<char> data = {static_cast<char>(200)};
    _tcpServer.send(client, data);
}
