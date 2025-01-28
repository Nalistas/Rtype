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

UdpClient::UdpClient()
    : _socket(_io_service)
{
}

UdpClient::~UdpClient() {
    // Fermer la socket proprement
    _socket.close();
}

void UdpClient::setServer(const std::string &ip, const std::string &port)
{
    asio::ip::udp::resolver resolver(_io_service);
    _results = resolver.resolve(asio::ip::udp::v4(), ip, port);
    _endpoint = *_results.begin();
    _socket.open(asio::ip::udp::v4());
}

void UdpClient::send(const std::vector<uint8_t> &message) {
    try {
        _socket.send_to(asio::buffer(message), _endpoint);
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
        buffer.resize(bytes_received);
    } catch (const std::exception &e) {
        std::cerr << "Receive error on server UDP: " << e.what() << std::endl;
    }
    return buffer;
}

bool UdpClient::hasData()
{
    return _socket.available() > 0;
}
