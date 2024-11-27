/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : resolver(io_context), socket(io_context)
{
    endpoint = *resolver.resolve(udp::v4(), "localhost", "5000").begin();
    socket.open(udp::v4());
}

Client::~Client() 
{
}

int Client::loop() 
{
    std::string message;
    while (true) {
        std::cout << "Entrez un message à envoyer au serveur (ou 'exit' pour quitter) : ";
        std::getline(std::cin, message);

        socket.send_to(asio::buffer(message), endpoint);

        if (message == "exit") {
            std::cout << "Fermeture du client..." << std::endl;
            break;
        }

        char reply[1024];
        udp::endpoint sender_endpoint;
        size_t reply_length = socket.receive_from(asio::buffer(reply, 1024), sender_endpoint);
        std::cout << "Réponse serveur : " << std::string(reply, reply_length) << std::endl;
    }
    return 0;
}
