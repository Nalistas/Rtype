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
    TcpProtocol tcp_protocol(_tcpServer);

    while (true) {
        auto client = _tcpServer.accept();

        if (!client) {
            continue;
        }

        if (_tcpServer._clients.find(client) == _tcpServer._clients.end()) {
            _tcpServer._clients[client] = "";
            for (auto &room : _tcpServer._rooms) {
                if (room.getName() == "lobby") {
                    room.addClient(client);
                }
            }
            tcp_protocol.listRooms(client);
        }

        std::cout << "Client connected." << std::endl;

        while (client) {
            state = _tcpServer.hasDataToRead(client);
            if (state == DATA) {
                std::vector<char> data = _tcpServer.receive(client);
                
                if (data.empty()) {
                    std::cout << "Client disconnected or read error." << std::endl;
                    break;
                }

                std::cout << "Received data: " << std::string(data.begin(), data.end()) << std::endl;
                tcp_protocol.interpreter(client, data);
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
