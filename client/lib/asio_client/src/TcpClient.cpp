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
    asio::ip::tcp::resolver resolver(_io_service);
    _results = resolver.resolve(asio::ip::tcp::v4(), ip, port);

    asio::connect(_socket, _results);
    std::cout << "Connected to TCP server at " << ip << ":" << port << std::endl;
}

TcpClient::~TcpClient()
{
    _socket.close();
}

void TcpClient::send(const std::vector<uint8_t> &message)
{
    if (message.empty()) {
        std::cerr << "Empty message" << std::endl;
        return;
    }
    if (message.size() > 65535) {
        std::cerr << "Message too long" << std::endl;
        return;
    }

    uint16_t length = static_cast<uint16_t>(message.size());
    std::vector<uint8_t> final_message(2 + message.size());
    final_message[0] = static_cast<uint8_t>(length / 256);
    final_message[1] = static_cast<uint8_t>(length & 0xFF);
    std::copy(message.begin(), message.end(), final_message.begin() + 2);

    try {
        asio::write(_socket, asio::buffer(final_message));
    } catch (const std::exception &e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

std::vector<uint8_t> TcpClient::receive()
{
    std::vector<uint8_t> length_buffer(2);
    std::vector<uint8_t> buffer;
    try {
        size_t length_received = _socket.read_some(asio::buffer(length_buffer, 2));

        if (length_received < 2) {
            std::cerr << "Incomplete length header received" << std::endl;
            return {};
        }
        uint16_t length = (static_cast<uint16_t>(length_buffer[0]) * 256) + static_cast<uint16_t>(length_buffer[1]);

        buffer.resize(length);

        size_t data_received = _socket.read_some(asio::buffer(buffer, length));

        // std::cout << "Received " << data_received << " bytes" << std::endl;

        if (data_received < length) {
            std::cerr << "Incomplete data received. Expected " << length << " bytes, but got " << data_received << " bytes." << std::endl;
            return {};
        }
    } catch (const std::exception &e) {
        std::cerr << "Receive error on server TCP: " << e.what() << std::endl;
        return {};
    }

    return buffer;
}

bool TcpClient::hasData()
{
    return _socket.available() > 0;
}
