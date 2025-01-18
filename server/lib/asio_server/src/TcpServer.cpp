/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TcpServer
*/

#include "TcpServer.hpp"
#include <iostream>

TcpServer::TcpServer(const std::string &ip, const std::string &port)
    : _endpoint(asio::ip::make_address(ip), std::stoi(port)),
      _acceptor(_io_service, _endpoint)
{
    std::cout << "Server initialized on " << ip << ":" << port << std::endl;
    _acceptor.non_blocking(true);
}

TcpServer::~TcpServer()
{
}


std::shared_ptr<asio::ip::tcp::socket> TcpServer::accept()
{
    auto client = std::make_shared<asio::ip::tcp::socket>(_io_service);
    
    asio::error_code ec;

    _acceptor.accept(*client, ec);

    if (ec) {
        std::cerr << "Error accepting connection: " << ec.message() << std::endl;
        return nullptr;
    } else {
        std::cout << "Client connected: " << client->remote_endpoint() << std::endl;
    }
    client->non_blocking(true);
    return client;
}

CLIENT_DATA_STATE TcpServer::hasDataToRead(std::shared_ptr<asio::ip::tcp::socket> client)
{
    asio::error_code ec;
    uint8_t temp_buffer[1];

    size_t bytes = client->receive(asio::buffer(temp_buffer, 1), asio::socket_base::message_peek, ec);

    if (ec == asio::error::would_block) {
        return EMPTY;
    } else if (ec) {
        if (ec == asio::error::eof) {
            std::cout << "Client disconnected" << std::endl;
            return DISCONNECTED;
        } else {
            std::cerr << "Error receiving: " << ec.message() << std::endl;
        }
        return CLIENT_ERROR;
    }

    return (bytes > 0) ? DATA : EMPTY;
}

std::vector<uint8_t> TcpServer::receive(std::shared_ptr<asio::ip::tcp::socket> client)
{
    std::vector<uint8_t> length_buffer(2);
    asio::error_code ec;

    size_t length_received = client->read_some(asio::buffer(length_buffer, 2),  ec);
    if (ec) {
        std::cerr << "Error receiving length header: " << ec.message() << std::endl;
        return {};
    }

    if (length_received < 2) {
        std::cerr << "Incomplete length header received" << std::endl;
        return {};
    }

    uint16_t length = (static_cast<uint16_t>(length_buffer[0]) * 256) + static_cast<uint16_t>(length_buffer[1]);

    std::vector<uint8_t> buffer(length);

    size_t data_received = client->read_some(asio::buffer(buffer, length), ec);
    if (ec) {
        std::cerr << "Error receiving data: " << ec.message() << std::endl;
        return {};
    }

    std::cout << "Received " << data_received << " bytes" << std::endl;

    if (data_received < length) {
        std::cerr << "Incomplete data received. Expected " << length << " bytes, but got " << data_received << " bytes." << std::endl;
        return {};
    }

    return buffer;
}

void TcpServer::send(std::shared_ptr<asio::ip::tcp::socket> client, const std::vector<uint8_t> &message)
{
    asio::error_code ec;

    if (message.size() > 65535) {
        std::cerr << "Message too long" << std::endl;
        return;
    }
    uint16_t length = static_cast<uint16_t>(message.size());
    std::vector<uint8_t> length_buffer = {static_cast<uint8_t>(length / 256), static_cast<uint8_t>(length & 0xFF)};

    asio::write(*client, asio::buffer(length_buffer), ec);
    asio::write(*client, asio::buffer(message), ec);

    if (ec) {
        std::cerr << "Error sending: " << ec.message() << std::endl;
    }
}
