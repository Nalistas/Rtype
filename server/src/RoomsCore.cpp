/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include "RoomsCore.hpp"
#include "TcpProtocol.hpp"
#include <string>
#include <iostream>

RoomsCore::RoomsCore(std::string const &port) :
    _tcpServer("0.0.0.0", port)
{}

RoomsCore::~RoomsCore()
{}

void RoomsCore::checkNewClients(void)
{
    auto client = _tcpServer.accept();

    if (!client) {
        return;
    }

    if (_clients.find(client) == _clients.end()) {
        _clients.insert({client, Client()});
    }
}

void RoomsCore::checkClients(TcpProtocol &tcpProtocol)
{
    CLIENT_DATA_STATE state;
    auto it = _clients.begin();
    
    while (it != _clients.end()) {
        state = _tcpServer.hasDataToRead(it->first);
        if (state == DATA) {
            auto client = it->first;
            treatClient(client, tcpProtocol);
        }
        if (state == DISCONNECTED || state == CLIENT_ERROR) {
            it->first->close();
            it = _clients.erase(it);
            std::cout << "Client disconnected." << std::endl;
            continue;
        }
        if (state == EMPTY) {
            continue;
        }
        ++it;
    }
}

void RoomsCore::treatClient(std::shared_ptr<asio::ip::tcp::socket> &client, TcpProtocol &tcpProtocol)
{
    std::vector<uint8_t> data = _tcpServer.receive(client);

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Received data from client: " << client << " \"" << this->_clients[client].getName() << "\"" << std::endl;
    std::cout << "Received data (Raw values): " << std::string(data.begin(), data.end()) << std::endl;
    for (uint8_t c : data) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << std::endl << std::endl << "Launching interpreter..." << std::endl;
    tcpProtocol.interpreter(client, data);
}

void RoomsCore::setGameToLaunch(uint8_t roomId)
{
    auto it = _rooms.find(roomId);

    if (it == _rooms.end()) {
        return;
    }
    this->_roomsToLaunch.emplace(*it);
    this->_rooms.erase(roomId);

    auto clientIt = this->_clients.begin();
    while (clientIt != this->_clients.end()) {
        if (clientIt->second.getRoomId() == roomId) {
            this->_clientsToLaunch.emplace(*clientIt);
            clientIt = this->_clients.erase(clientIt);
        } else {
            ++clientIt;
        }
    }
}

void RoomsCore::launchGame()
{
    // launch the game to launch
}


void RoomsCore::run(void)
{
    std::function<void(uint8_t roomId)> launchGame = [this](uint8_t roomId) { this->setGameToLaunch(roomId); };
    TcpProtocol tcp_protocol(_rooms, _clients, _tcpServer, launchGame);

    while (true) {
        checkNewClients();
        checkClients(tcp_protocol);
    }
}
