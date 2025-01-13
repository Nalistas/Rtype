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


TcpProtocol::TcpProtocol(TcpServer &server) : _tcpServer(server)
{
    _commandMap[1] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Set name
        std::string name;
        params >> name;
        _tcpServer._clients[client] = name;
        std::cout << "Set " << _tcpServer._clients[client] << " name\n";
        std::vector<uint8_t> data = {200};
        std::cout << "data ready\n";
        _tcpServer.send(client, data);
        std::cout << "data sent\n";
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
        (void)params;
        exitRoom(client);
        std::cout << "Exit room\n";
    };
    _commandMap[5] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Rename room
        int roomId;
        std::string roomName;

        params >> roomId;
        params.get();
        std::getline(params, roomName);
        renameRoom(client, roomId, roomName);
        std::cout << "Rename room\n";
    };
    _commandMap[7] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Create room
        std::string roomName;
        std::string gameName;

        std::getline(params, roomName, '\\');
        std::getline(params, gameName); 
        createRoom(client, roomName, gameName);
        std::cout << "Create room\n";
    };
    _commandMap[8] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // List rooms
        (void)params;
        listRooms(client);
        std::cout << "List rooms\n";
    };
    _commandMap[9] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Del room
        params.get();
        int roomId;
        params >> roomId;
        deleteRoom(client, roomId);
        std::cout << "Delete room\n";
    };
    _commandMap[10] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        // Change Status client
        (void)params;
        for (auto &room : _tcpServer._rooms) {
            if (room.isClientInRoom(client)) {
                room.changeClientStatus(client);
            }
        }
        std::cout << "Change Status client\n";
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<uint8_t> data)
{
    std::istringstream stream(std::string(data.begin(), data.end()));
    uint8_t commandId;
    stream >> commandId;

    if (_commandMap.find(commandId) != _commandMap.end()) {
        std::cout << "Command founded\n";
        _commandMap[commandId](client, stream);
        std::cout << "Command executed\n";
        return 0;
    } else {
        std::cout << "Command not founded\n";
        std::vector<uint8_t> data = {static_cast<uint8_t>(201)};
        _tcpServer.send(client, data);
    }
    return 0;
}

void TcpProtocol::listRooms(std::shared_ptr<asio::ip::tcp::socket> client)
{
    std::vector<uint8_t> allData;

    for (auto &room : _tcpServer._rooms) {
        allData.push_back(room.getId());
        const std::string& roomName = room.getName();
        allData.insert(allData.end(), roomName.begin(), roomName.end());
        allData.push_back('\\');
        int personCount = room.getNbClients();
        allData.push_back(static_cast<uint8_t>(personCount));
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
            std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
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
            std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
            _tcpServer.send(client, data);
            return;
        }
    }
}

void TcpProtocol::createRoom(std::shared_ptr<asio::ip::tcp::socket> client, std::string roomName, std::string gameName)
{
    Room newRoom(roomName, gameName, _tcpServer._rooms.size());
    newRoom.setOwner(client);
    _tcpServer._rooms.push_back(newRoom);
    std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
    _tcpServer.send(client, data);
}

void TcpProtocol::renameRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId, std::string roomName)
{
    for (auto &room : _tcpServer._rooms) {
        if (room.getId() == roomId) {
            if (room.getOwner() != client) {
                std::vector<uint8_t> data = {static_cast<uint8_t>(201)};
                _tcpServer.send(client, data);
                return;
            }
            room.setName(roomName);
            std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
            _tcpServer.send(client, data);
            return;
        }
    }
}

void TcpProtocol::deleteRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId)
{
    for (auto &room : _tcpServer._rooms) {
        if (room.getId() == roomId) {
            if (room.getOwner() != client) {
                std::vector<uint8_t> data = {static_cast<uint8_t>(201)};
                _tcpServer.send(client, data);
                return;
            }
            _tcpServer._rooms.erase(_tcpServer._rooms.begin() + roomId);
            std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
            _tcpServer.send(client, data);
            return;
        }
    }
}

std::vector<uint8_t> TcpProtocol::image_to_binary(const std::string &path)
{
    std::ifstream imageFile(path, std::ios::binary);
    if (!imageFile) {
        std::cerr << "Erreur lors de l'ouverture de l'image !" << std::endl;
        return {};
    }

    imageFile.seekg(0, std::ios::end);
    std::streamsize imageSize = imageFile.tellg();
    imageFile.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(imageSize);
    if (!imageFile.read(reinterpret_cast<char*>(buffer.data()), imageSize)) {
        std::cerr << "Erreur lors de la lecture de l'image !" << std::endl;
        return {};
    }
    return buffer;
}

void TcpProtocol::sendImage(std::shared_ptr<asio::ip::tcp::socket> client, uint8_t spriteId, uint32_t sizeX, uint32_t sizeY, uint32_t width, uint32_t height,
    uint32_t offsetX, uint32_t offsetY, uint8_t nbFrames, uint32_t frameDelay, const std::string &path)
{
    std::vector<uint8_t> data;

    data.push_back(spriteId);
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&sizeX), reinterpret_cast<uint8_t*>(&sizeX) + sizeof(sizeX));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&sizeY), reinterpret_cast<uint8_t*>(&sizeY) + sizeof(sizeY));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&width), reinterpret_cast<uint8_t*>(&width) + sizeof(width));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&height), reinterpret_cast<uint8_t*>(&height) + sizeof(height));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&offsetX), reinterpret_cast<uint8_t*>(&offsetX) + sizeof(offsetX));
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&offsetY), reinterpret_cast<uint8_t*>(&offsetY) + sizeof(offsetY));
    data.push_back(nbFrames);
    data.insert(data.end(), reinterpret_cast<uint8_t*>(&frameDelay), reinterpret_cast<uint8_t*>(&frameDelay) + sizeof(frameDelay));

    std::vector<uint8_t> imageData = image_to_binary(path);
    data.insert(data.end(), imageData.begin(), imageData.end());

    _tcpServer.send(client, data);
}
