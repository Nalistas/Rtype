/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string &hostname) : resolver(io_context), socket(io_context) {
    // Utilisation du hostname pour résoudre l'adresse du serveur
    endpoint = *resolver.resolve(udp::v4(), hostname, "5000").begin();
    socket.open(udp::v4());
}

Client::~Client() 
{
}

void Client::send_message(const std::string &message) 
{
    socket.send_to(asio::buffer(message), endpoint);

    char reply[1024];
    udp::endpoint sender_endpoint;
    size_t reply_length = socket.receive_from(asio::buffer(reply, 1024), sender_endpoint);
    std::cout << "Réponse serveur : " << std::string(reply, reply_length) << std::endl;
}

int Client::loop() 
{
    return 0;
}
