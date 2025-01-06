/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TcpClient
*/

#include "TcpClient.hpp"
#include <iostream>

TcpClient::TcpClient(const std::string &ip, const std::string &port)
    : _socket(_io_service)
{
    // Résolution de l'adresse et du port
    asio::ip::tcp::resolver resolver(_io_service);
    _results = resolver.resolve(asio::ip::tcp::v4(), ip, port);

    // Connexion au serveur
    asio::connect(_socket, _results);
    std::cout << "Connected to TCP server at " << ip << ":" << port << std::endl;
}

TcpClient::~TcpClient() {
    // Fermer la socket proprement
    _socket.close();
}

void TcpClient::send(const std::vector<char> &message) {
    try {
        asio::write(_socket, asio::buffer(message));
        std::cout << "Message sent successfully" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

std::vector<char> TcpClient::receive() {
    std::vector<char> buffer(1024); // Taille maximale du tampon
    try {
        size_t bytes_received = _socket.read_some(asio::buffer(buffer));
        buffer.resize(bytes_received); // Ajuster la taille des données reçues
    } catch (const std::exception &e) {
        std::cerr << "Receive error: " << e.what() << std::endl;
    }
    return buffer;
}

bool TcpClient::hasData() {
    return _socket.available() > 0;
}
