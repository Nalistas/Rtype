/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : resolver(io_context), socket(io_context) {
    // Initialisation sans connexion directe
    connected = false;
}

Client::~Client() 
{
    if (socket.is_open()) {
        socket.close();
    }
}

bool Client::connect(const std::string &hostname) 
{
    try {
        // Résolution de l'adresse et du port
        endpoint = *resolver.resolve(udp::v4(), hostname, "5000").begin();
        socket.open(udp::v4());
        connected = true;
    } catch (const std::exception &e) {
        std::cerr << "Erreur de connexion : " << e.what() << std::endl;
        connected = false;
    }
    return connected;
}

void Client::send_message(const std::string &message) 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return;
    }
    socket.send_to(asio::buffer(message), endpoint);
}

bool Client::has_data() 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return false;
    }

    asio::socket_base::bytes_readable command(true);
    socket.io_control(command);
    return command.get() > 0;
}

std::string Client::get_data() 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return "";
    }

    char buffer[1024];
    udp::endpoint sender_endpoint;

    try {
        size_t reply_length = socket.receive_from(asio::buffer(buffer, 1024), sender_endpoint);
        return std::string(buffer, reply_length);
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
        return "";
    }
}
