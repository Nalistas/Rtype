#include "UdpServer.hpp"
#include <iostream>

UdpServer::UdpServer(void) :
    _resolver(_io_context), _socket(_io_context)
{
    uint16_t start_port = 2000;
    uint16_t end_port = 0xFFFF;

    for (uint16_t port = start_port; port < end_port; ++port) {
        try {
            _endpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), port);
            _socket.open(asio::ip::udp::v4());
            _socket.bind(_endpoint);
            break;
        } catch (const std::exception &e) {
            std::cerr << "Failed to bind on port " << port << ": " << e.what() << std::endl;
            _socket.close(); // Close socket on failure to avoid lingering state
        }
    }
    std::cout << "Server started on port " << _endpoint.port() << "." << std::endl;
}

UdpServer::UdpServer(int port) :
    _resolver(_io_context), _socket(_io_context)
{
    try {
        _endpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), port);
        _socket.open(asio::ip::udp::v4());
        _socket.bind(_endpoint);
        _socket.non_blocking(true);
        std::cout << "Server started on port " << port << "." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error when starting server : " << e.what() << "at : " << __FILE__ << ":" << __LINE__ << std::endl;
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

void UdpServer::sendTo(asio::ip::udp::endpoint const &endpoint, std::vector<uint8_t> const &data)
{
    try {
        _socket.send_to(asio::buffer(data), endpoint);
        // std::cout << "Réponse envoyée à " << endpoint.address().to_string() 
        //           << ":" << endpoint.port() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi de la réponse : " << e.what() << std::endl;
    }
}

void UdpServer::readFrom(asio::ip::udp::endpoint &endpoint, std::vector<uint8_t> &data)
{
    data.resize(1024);

    try {
        size_t bytes_received = _socket.receive_from(asio::buffer(data), endpoint);
        data.resize(bytes_received);
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
    }
}

asio::ip::udp::endpoint UdpServer::getEndpoint(void) const
{
    return _endpoint;
}
