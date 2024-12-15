/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "AsioApi.hpp"

rtype_protocol::AsioApi::AsioApi() : resolver(io_context), socket(io_context) {
    connected = false;
}

rtype_protocol::AsioApi::~AsioApi() 
{
    if (socket.is_open()) {
        socket.close();
    }
}

bool rtype_protocol::AsioApi::connect(const std::string &hostname, const std::string &port) 
{
    try {
        udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), hostname, port);
        endpoint = *endpoints.begin();
        socket.open(udp::v4());
        connected = true;
        std::cout << "Connexion réussie à " << hostname << " sur le port " << port << "." << std::endl;
        send_message({1, 0});
    } catch (const std::exception &e) {
        std::cerr << "Erreur de connexion : " << e.what() << std::endl;
        connected = false;
    }
    return connected;
}

void rtype_protocol::AsioApi::send_message(const std::vector<char> &message) 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return;
    }
    try {
        socket.send_to(asio::buffer(message), endpoint);
        std::cout << "Message envoyé." << std::endl;
        for (char c : message) std::cout << static_cast<int>(c) << " ";
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi du message : " << e.what() << std::endl;
    }
}

bool rtype_protocol::AsioApi::has_data() 
{
    try {
        asio::socket_base::bytes_readable command(true);
        socket.io_control(command);
        return command.get() > 0;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la vérification des données : " << e.what() << std::endl;
        return false;
    }
}

rtype_protocol::AsioApi::UDP_DATA rtype_protocol::AsioApi::get_data() 
{
    char buffer[1024];
    udp::endpoint sender_endpoint;

    try {
        size_t reply_length = socket.receive_from(asio::buffer(buffer, 1024), sender_endpoint);

        UDP_DATA received_data;
        received_data.data = std::vector<char>(buffer, buffer + reply_length);
        received_data.sender_endpoint = sender_endpoint;

        std::string reply(received_data.data.begin(), received_data.data.end());
        std::cout << "Réponse reçue : " << reply << std::endl;

        return received_data;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
        return UDP_DATA();
    }
}

bool rtype_protocol::AsioApi::start_server(const std::string &port) 
{
    try {
        udp::endpoint local_endpoint(udp::v4(), std::stoi(port));
        socket.open(udp::v4());
        socket.bind(local_endpoint);
        std::cout << "Serveur démarré sur le port " << port << "." << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors du démarrage du serveur : " << e.what() << std::endl;
        return false;
    }
}

// Nouvelle méthode : Répondre à un client
void rtype_protocol::AsioApi::reply_to(const UDP_DATA &client_data) 
{
    try {
        socket.send_to(asio::buffer(client_data.data), client_data.sender_endpoint);
        std::cout << "Réponse envoyée à " << client_data.sender_endpoint.address().to_string() 
                  << ":" << client_data.sender_endpoint.port() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi de la réponse : " << e.what() << std::endl;
    }
}

