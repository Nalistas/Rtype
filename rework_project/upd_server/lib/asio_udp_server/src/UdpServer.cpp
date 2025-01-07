#include "UdpServer.hpp"
#include <iostream>

UdpServer::UdpServer(const std::string &port) :
    _resolver(_io_context), _socket(_io_context)
{
    try {
        asio::ip::udp::endpoint local_endpoint(asio::ip::udp::v4(), std::stoi(port));
        _socket.open(asio::ip::udp::v4());
        _socket.bind(local_endpoint);
        std::cout << "Serveur démarré sur le port " << port << "." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors du démarrage du serveur : " << e.what() << std::endl;
        throw std::runtime_error("Failed to start server");
    }
}

UdpServer::~UdpServer()
{
}

bool UdpServer::hasDataToRead(void)
{
    try {
        asio::socket_base::bytes_readable command(true);
        _socket.io_control(command);
        return command.get() > 0;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la vérification des données : " << e.what() << std::endl;
        return false;
    }
}

void UdpServer::sendTo(asio::ip::udp::endpoint const &endpoint, std::vector<char> const &data)
{
    try {
        _socket.send_to(asio::buffer(data), endpoint);
        std::cout << "Réponse envoyée à " << endpoint.address().to_string() 
                  << ":" << endpoint.port() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi de la réponse : " << e.what() << std::endl;
    }
}

void UdpServer::readFrom(asio::ip::udp::endpoint &endpoint, std::vector<char> &data)
{
    data.resize(1024);

    try {
        size_t bytes_received = _socket.receive_from(asio::buffer(data), endpoint);
        data.resize(bytes_received);
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
    }
}
