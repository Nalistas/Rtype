/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server() : socket(io_context, udp::endpoint(udp::v4(), 5000))
{
}

Server::~Server() 
{
}

int Server::loop() 
{
    while (true) {
        char data[1024];
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(asio::buffer(data, 1024), sender_endpoint);

        std::string message(data, length);
        std::cout << "Message reçu de " << sender_endpoint.address().to_string()
                  << ":" << sender_endpoint.port() << " -> " << message << std::endl;

        // add client if not exist
        // if (clients.find(sender_endpoint) == clients.end()) {
        //     clients[sender_endpoint] = {};
        //     std::cout << "Nouveau client ajouté : " 
        //               << sender_endpoint.address().to_string()
        //               << ":" << sender_endpoint.port() << std::endl;
        // }

        // Préparer une réponse
        std::string reply = "Echo: " + message;
        socket.send_to(asio::buffer(reply), sender_endpoint);
    }

    return 0;
}
