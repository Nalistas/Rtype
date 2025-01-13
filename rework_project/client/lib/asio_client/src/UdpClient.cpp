#include "UdpClient.hpp"
#include <iostream>

UdpClient::UdpClient(const std::string &ip, const std::string &port)
    : _socket(_io_service)
{
    asio::ip::udp::resolver resolver(_io_service);
    _results = resolver.resolve(asio::ip::udp::v4(), ip, port);
    _endpoint = *_results.begin();
    _socket.open(asio::ip::udp::v4());
}

UdpClient::~UdpClient() {
    // Fermer la socket proprement
    _socket.close();
}

void UdpClient::send(const std::vector<uint8_t> &message) {
    try {
        _socket.send_to(asio::buffer(message), _endpoint);
        std::cout << "Message sent successfully" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

std::vector<uint8_t> UdpClient::receive()
{
    std::vector<uint8_t> buffer(1024);

    try {
        asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_received = _socket.receive_from(asio::buffer(buffer), sender_endpoint);
        buffer.resize(bytes_received); // Ajuster la taille des données reçues
    } catch (const std::exception &e) {
        std::cerr << "Receive error: " << e.what() << std::endl;
    }
    return buffer;
}

bool UdpClient::hasData()
{
    return _socket.available() > 0;
}
