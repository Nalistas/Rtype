/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : resolver(io_context), socket(io_context) {
    connected = false;
}

Client::~Client() 
{
    if (socket.is_open()) {
        socket.close();
    }
}

bool Client::connect(const std::string &hostname, const std::string &port) 
{
    try {
        udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), hostname, port);
        endpoint = *endpoints.begin();
        socket.open(udp::v4());
        connected = true;
        std::cout << "Connexion réussie à " << hostname << " sur le port " << port << "." << std::endl;
        send_message("Connect");
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
    try {
        socket.send_to(asio::buffer(message), endpoint);
        std::cout << "Message envoyé : " << message << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi du message : " << e.what() << std::endl;
    }
}

bool Client::has_data() 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return false;
    }

    try {
        asio::socket_base::bytes_readable command(true);
        socket.io_control(command);
        return command.get() > 0;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la vérification des données : " << e.what() << std::endl;
        return false;
    }
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
        std::string reply(buffer, reply_length);
        std::cout << "Réponse reçue : " << reply << std::endl;
        return reply;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
        return "";
    }
}
