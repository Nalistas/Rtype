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
        std::cout << "Message reçu : " << std::string(data, length) << std::endl;

        std::string reply(data, length);
        socket.send_to(asio::buffer(reply), sender_endpoint);
    }
    return 0;
}

