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
        return nullptr;
    } else {
        std::cout << "Client connected: " << client->remote_endpoint() << std::endl;
    }

    return client;
}

CLIENT_DATA_STATE TcpServer::hasDataToRead(std::shared_ptr<asio::ip::tcp::socket> client)
{
    asio::error_code ec;
    char temp_buffer[1];

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
        return ERROR;
    }

    return (bytes > 0) ? DATA : EMPTY;
}

std::vector<char> TcpServer::receive(std::shared_ptr<asio::ip::tcp::socket> client)
{
    std::vector<char> buffer(1024);
    asio::error_code ec;

    std::cout << "Hello" << std::endl;

    size_t length = client->read_some(asio::buffer(buffer), ec);

    std::cout << "Received " << length << " bytes" << std::endl;

    if (ec) {
        if (ec == asio::error::eof) {
            std::cout << "Client disconnected" << std::endl;
        } else {
            std::cerr << "Error receiving: " << ec.message() << std::endl;
        }
        return {};
    }

    buffer.resize(length);
    return buffer;
}

void TcpServer::send(std::shared_ptr<asio::ip::tcp::socket> client, const std::vector<char> &message)
{
    asio::error_code ec;
    
    // Bloque jusqu'à ce que le message soit envoyé
    asio::write(*client, asio::buffer(message), ec);

    if (ec) {
        std::cerr << "Error sending: " << ec.message() << std::endl;
    }
}
