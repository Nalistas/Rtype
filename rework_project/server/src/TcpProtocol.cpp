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


TcpProtocol::TcpProtocol(
    std::map<uint8_t, Room> &rooms,
    std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &clients, 
    TcpServer &tcpServer
) : _rooms(rooms), _clients(clients), _tcpServer(tcpServer)
{
    _commandMap[1] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Set name
        std::string name;
        params >> name;
        _clients[client].setName(name);
        std::cout << "Set " << _clients[client].getName() << " name\n";
        std::vector<uint8_t> data = {200};
        std::cout << "data ready\n";
        _tcpServer.send(client, data);
        std::cout << "data sent\n";
    };
    _commandMap[2] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Enter room
        uint8_t roomId;
        params >> roomId;
        enterRoom(client, roomId);
        std::cout << "Enter room\n";
    };
    _commandMap[4] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Exit room
        (void)params;
        exitRoom(client);
        std::cout << "Exit room\n";
    };
    _commandMap[5] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Rename room
        uint8_t roomId;
        std::string roomName;

        params >> roomId;
        params.get();
        std::getline(params, roomName);
        renameRoom(client, roomId, roomName);
        std::cout << "Rename room\n";
    };
    _commandMap[7] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Create room
        std::string roomName;
        std::string gameName;

        std::getline(params, roomName, '\\');
        std::getline(params, gameName); 
        createRoom(client, roomName, gameName);
        std::cout << "Create room\n";
    };
    _commandMap[8] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // List rooms
        (void)params;
        listRooms(client);
        std::cout << "List rooms\n";
    };
    _commandMap[9] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Del room
        params.get();
        uint8_t roomId;
        params >> roomId;
        deleteRoom(client, roomId);
        std::cout << "Delete room\n";
    };
    _commandMap[10] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Change Status client
        (void)params;
        auto it = this->_clients.find(client);
        if (it != this->_clients.end() && it->second.getRoomId() != 0) {
            this->_clients[client].setReady(!this->_clients[client].isReady());
        }
        std::cout << "Change Status client\n";
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::shared_ptr<asio::ip::tcp::socket> &client, std::vector<uint8_t> data)
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

void TcpProtocol::listRooms(std::shared_ptr<asio::ip::tcp::socket> &client)
{

    for (auto &room : _rooms) {
        std::vector<uint8_t> allData({1, 1}); // {1, 2} => la room vient d'être delete {1, 1} => 

        allData.push_back(room.first);
        const std::string& roomName = room.second.getName();
        allData.insert(allData.end(), roomName.begin(), roomName.end());
        allData.push_back('\\');
        int personCount = 0;
        for (auto &client : _clients) {
            if (client.second.getRoomId() == room.first) {
                personCount++;
            }
        }
        allData.push_back(static_cast<uint8_t>(personCount));
        // allData.push_back('#');
        _tcpServer.send(client, allData);
    }
}

void TcpProtocol::enterRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId)
{
    auto it = this->_rooms.find(roomId);
    auto it2 = this->_clients.find(client);

    if (it != this->_rooms.end() && it2 != this->_clients.end()) {
        this->_clients[client].setRoomId(roomId);
        std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
        _tcpServer.send(client, data);
    }
}

void TcpProtocol::exitRoom(std::shared_ptr<asio::ip::tcp::socket> &client)
{
    auto it = this->_clients.find(client);
    uint8_t roomId = this->_clients[client].getRoomId();

    if (it != this->_clients.end()) {
        this->_clients[client].setRoomId(0);
        std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
        _tcpServer.send(client, data);
    }
    for (auto &client : this->_clients) {
        if (client.second.getRoomId() == roomId) {
            return;
        }
    }
    this->_rooms.erase(roomId);
}

void TcpProtocol::createRoom(std::shared_ptr<asio::ip::tcp::socket> &client, std::string roomName, std::string gameName)
{
    this->_rooms.emplace(this->_rooms.size(), Room(roomName, gameName, client));
    std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
    _tcpServer.send(client, data);
}

void TcpProtocol::renameRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId, std::string roomName)
{
    auto it = this->_rooms.find(roomId);
    if (it != this->_rooms.end() && it->second.getOwner() == client) {
        it->second.setName(roomName);
    }
}

void TcpProtocol::deleteRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId)
{
    auto it = this->_rooms.find(roomId);
    if (it != this->_rooms.end() && it->second.getOwner() == client) {
        for (auto client : this->_clients) {
            this->_tcpServer.send(client.first, {1, 2, it->first});
        }
        this->_rooms.erase(it);
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

void TcpProtocol::copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value)
{
    vec[pos] = value & 0xFF;
    vec[pos + 1] = (value >> 8) & 0xFF;
    vec[pos + 2] = (value >> 16) & 0xFF;
    vec[pos + 3] = (value >> 24) & 0xFF;
}
