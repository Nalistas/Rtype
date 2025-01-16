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
    _commandMap[SET_NAME] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        std::string name;
        params >> name;
        this->setName(client, name);
    };
    _commandMap[ENTER_ROOM] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        uint8_t roomId;
        params >> roomId;
        enterRoom(client, roomId);
    };
    _commandMap[LEAVE_ROOM] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        (void)params;
        exitRoom(client);
    };
    _commandMap[CREATE_ROOM] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        std::string roomName;
        std::string gameName;

        std::getline(params, roomName, '\\');
        std::getline(params, gameName); 
        createRoom(client, roomName, gameName);
    };
    _commandMap[LIST_ROOMS] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        (void)params;
        listRooms(client);
        std::cout << "List rooms\n";
    };
    _commandMap[DELETE_ROOM] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        params.get();
        uint8_t roomId;
        params >> roomId;
        deleteRoom(client, roomId);
    };
    _commandMap[SET_READY] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        // Change Status client
        (void)params;
        auto it = this->_clients.find(client);
        if (it != this->_clients.end() && it->second.getRoomId() != 0) {
            this->_clients[client].setReady(!this->_clients[client].isReady());
        }
        std::cout << "Change Status client of " << client << std::endl;
        std::vector<uint8_t> data = {200};
        _tcpServer.send(client, data);
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
    }
    std::cout << "Command not found\n";
    std::vector<uint8_t> response = {static_cast<uint8_t>(201)};
    _tcpServer.send(client, response);
    std::cout << "--------------------------\n";
    return 0;
}


void TcpProtocol::setName(std::shared_ptr<asio::ip::tcp::socket> &client, std::string name)
{
    std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
    auto it = this->_clients.find(client);

    if (it != this->_clients.end()) {
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
    std::vector<uint8_t> data = {200};
    auto it = this->_rooms.find(roomId);
    auto it2 = this->_clients.find(client);

    if (it != this->_rooms.end() && it2 != this->_clients.end() && it2->second.getName() != "") {
        this->_clients[client].setRoomId(roomId);
        _tcpServer.send(client, data);
        std::cout << "Client " << it2->second.getName() << " entered room " << roomId << std::endl; 
    } else {
        data[0] = {201};
        _tcpServer.send(client, data);
        std::cout << "Client " << client << " error when entering the room " << roomId << std::endl;
    }
}

void TcpProtocol::exitRoom(std::shared_ptr<asio::ip::tcp::socket> &client)
{
    auto it = this->_clients.find(client);
    uint8_t roomId = this->_clients[client].getRoomId();
    auto roomIt = this->_rooms.find(roomId);
    std::vector<uint8_t> data = {200};

    if (roomIt == this->_rooms.end()) {
        this->_clients[client].setRoomId(0);
        _tcpServer.send(client, data);
        std::cout << "Client " << client << " room not found, putting him in lobbie (0)" << std::endl;
        return;
    }

    if (it != this->_clients.end()) {
        this->_clients[client].setRoomId(0);
        _tcpServer.send(client, data);
        std::cout << "Client " << it->second.getName() << " exited room " << roomId << std::endl;
    } else {
        data[0] = {201};
        _tcpServer.send(client, data);
        std::cout << "Client " << client << " not found, room not exited" << std::endl;
        return;
    }

    for (auto &clientIt : this->_clients) {
        if (clientIt.second.getRoomId() == roomId) {
            if (client == roomIt->second.getOwner()) {
                auto tmp = clientIt.first;
                roomIt->second.setOwner(tmp);
                std::cout << "Room " << roomId << " owner changed to " << tmp << std::endl;
            }
            return;
        }
    }
    std::cout << "No clients in room " << roomId << ", room will be deleted" << std::endl;
    roomIt->second.setOwner(client);
    deleteRoom(client, roomId);
}

void TcpProtocol::createRoom(std::shared_ptr<asio::ip::tcp::socket> &client, std::string roomName, std::string gameName)
{
    uint8_t roomId = 1;
    std::vector<uint8_t> data = {static_cast<uint8_t>(200)};
    auto client_it = this->_clients.find(client);

    if (client_it == this->_clients.end() || client_it->second.getName() == "") {
        data[0] = static_cast<uint8_t>(KO);
        _tcpServer.send(client, data);
        std::cout << "Client not found or doesn't have a name" << std::endl;
        return;
    }

    for (uint8_t i = 1; i < 255; i++) {
        if (this->_rooms.find(i) == this->_rooms.end()) {
            roomId = i;
            break;
        }
    }

    if (roomId == 255 && this->_rooms.find(roomId) != this->_rooms.end()) {
        data[0] = static_cast<uint8_t>(KO);
        _tcpServer.send(client, data);
        std::cout << "Too many rooms" << std::endl;
        return;
    }

    this->_rooms.emplace(roomId, Room(roomName, gameName, client));
    client_it->second.setRoomId(roomId);

    _tcpServer.send(client, data);

    data = {1, 1, roomId};
    data.insert(data.end(), roomName.begin(), roomName.end());
    data.push_back('\\');
    data.push_back(static_cast<uint8_t>(1));

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

void TcpProtocol::broadcast(std::vector<uint8_t> data)
{
    for (auto &client : this->_clients) {
        _tcpServer.send(client.first, data);
    }
}
