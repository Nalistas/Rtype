/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include <iostream>
#include "TcpServer.hpp"

int main() {
    TcpServer server("127.0.0.1", "12345");
    CLIENT_DATA_STATE state;

    while (true) {
        auto client = server.accept();

        if (!client) {
            continue;
        }

        std::cout << "Client connected." << std::endl;

        while (client) {
            state = server.hasDataToRead(client);
            if (state == DATA) {
                std::vector<char> data = server.receive(client);
                
                if (data.empty()) {
                    std::cout << "Client disconnected or read error." << std::endl;
                    break;
                }

                std::cout << "Received data: " << std::string(data.begin(), data.end()) << std::endl;

                server.send(client, data);
            }
            if (state == DISCONNECTED) {
                break;
            }
            if (state == ERROR) {
                break;
            }
        }
        client->close();
        std::cout << "Connection closed." << std::endl;
    }

    return 0;
}
