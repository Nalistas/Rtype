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

void RoomsCore::run(void)
{
    CLIENT_DATA_STATE state;
    TcpProtocol tcp_protocol(_rooms, _clients, _tcpServer);

    while (true) {
        auto client = _tcpServer.accept();

        if (!client) {
            continue;
        }

        if (_clients.find(client) == _clients.end()) {
            _clients.insert({client, Client()});
        }

        std::cout << "Client connected." << std::endl;

        while (client) {
            state = _tcpServer.hasDataToRead(client);
            if (state == DATA) {
                std::vector<uint8_t> data = _tcpServer.receive(client);
                
                if (data.empty()) {
                    std::cout << "Client disconnected or read error." << std::endl;
                    break;
                }

                std::cout << "Received data (ASCII values): " << std::string(data.begin(), data.end()) << std::endl;
                for (uint8_t c : data) {
                    std::cout << static_cast<int>(c) << " ";
                }
                std::cout << std::endl;
                // std::cout << "Received data: " << std::string(data.begin(), data.end()) << std::endl;
                tcp_protocol.interpreter(client, data);
                std::cout << "Rooms: " << std::endl;
                for (auto &room : _rooms) {
                    std::cout << "Room: " << room.second.getName() << "  "<< room.second.getGameName() << std::endl;
                }
                std::cout << "---------------------------------------------------------" << std::endl << "Clients: " << std::endl;
                for (auto &client : _clients) {
                    std::cout << "Client: " << client.first << " " << client.second.getName() << " " << static_cast<int>(client.second.getRoomId()) << std::endl;
                }
                std::cout << "---------------------------------------------------------" << std::endl;
                std::cout << std::endl;
                // _tcpServer.send(client, data);
            }
            if (state == DISCONNECTED) {
                break;
            }
            if (state == CLIENT_ERROR) {
                break;
            }
        }
        client->close();
        std::cout << "Connection closed." << std::endl;
    }
}
