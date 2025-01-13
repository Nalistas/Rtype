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
    std::cout << "Received data from client: " << client << std::endl;
    std::cout << "Received data (ASCII values): " << std::string(data.begin(), data.end()) << std::endl;
    for (uint8_t c : data) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    tcpProtocol.interpreter(client, data);
}

void RoomsCore::run(void)
{
    TcpProtocol tcp_protocol(_rooms, _clients, _tcpServer);

    while (true) {
        checkNewClients();
        checkClients(tcp_protocol);

        // std::cout << "Client connected." << std::endl;

        // while (client) {
        //     state = _tcpServer.hasDataToRead(client);
        //     if (state == DATA) {
        //         std::vector<uint8_t> data = _tcpServer.receive(client);
                
        //         if (data.empty()) {
        //             std::cout << "Client disconnected or read error." << std::endl;
        //             break;
        //         }

        //         std::cout << "Received data (ASCII values): " << std::string(data.begin(), data.end()) << std::endl;
        //         for (uint8_t c : data) {
        //             std::cout << static_cast<int>(c) << " ";
        //         }
        //         std::cout << std::endl;
        //         // std::cout << "Received data: " << std::string(data.begin(), data.end()) << std::endl;
        //         tcp_protocol.interpreter(client, data);
        //         std::cout << "Rooms: " << std::endl;
        //         for (auto &room : _rooms) {
        //             std::cout << "Room: " << room.second.getName() << "  "<< room.second.getGameName() << std::endl;
        //         }
        //         std::cout << "---------------------------------------------------------" << std::endl << "Clients: " << std::endl;
        //         for (auto &client : _clients) {
        //             std::cout << "Client: " << client.first << " " << client.second.getName() << " " << static_cast<int>(client.second.getRoomId()) << std::endl;
        //         }
        //         std::cout << "---------------------------------------------------------" << std::endl;
        //         std::cout << std::endl;
        //         // _tcpServer.send(client, data);
        //     }
        //     if (state == DISCONNECTED) {
        //         break;
        //     }
        //     if (state == CLIENT_ERROR) {
        //         break;
        //     }
        // }
        // client->close();
        // std::cout << "Connection closed." << std::endl;
    }
}
