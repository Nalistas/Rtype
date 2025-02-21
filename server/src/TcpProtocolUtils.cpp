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
    TcpServer &tcpServer,
    std::function<void(uint8_t roomId)> launchGame,
    std::vector<std::string> &gameList
) : _rooms(rooms), _clients(clients), _tcpServer(tcpServer), _launchGame(launchGame), _gameList(gameList)
{
    for (auto ele: _gameList) {
        std::cout << ele << std::endl;
    }

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
        (void)params;
        changeStatus(client);
    };
    _commandMap[LIST_GAMES] = [this](std::shared_ptr<asio::ip::tcp::socket> &client, std::istringstream& params) {
        (void)params;
        listGames(client);
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::shared_ptr<asio::ip::tcp::socket> &client, std::vector<uint8_t> data)
{
    uint8_t commandId = data[0];
    std::istringstream stream(std::string(data.begin() + 1, data.end()));
    // stream >> commandId;

    if (_commandMap.find(commandId) != _commandMap.end()) {
        _commandMap[commandId](client, stream);
        return 0;
    }
    std::cout << "Command not found : " << static_cast<int>(commandId) << std::endl;
    std::vector<uint8_t> response = {static_cast<uint8_t>(201)};
    _tcpServer.send(client, response);
    std::cout << "--------------------------\n";
    return 0;
}

std::shared_ptr<asio::ip::tcp::socket> TcpProtocol::isRoomEmpty(uint8_t roomId)
{
    for (auto &clientIt : this->_clients) {
        if (clientIt.second.getRoomId() == roomId) {
            return clientIt.first;
        }
    }
    return nullptr;
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
