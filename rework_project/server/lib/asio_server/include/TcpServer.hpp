/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
    #define TCPSERVER_HPP_

#include <string>
#include <vector>
#include <asio.hpp>
#include <optional>
#include <map>

enum CLIENT_DATA_STATE {
    EMPTY = 0,
    DATA = 1,
    DISCONNECTED = 2,
    CLIENT_ERROR = 3
};

class TcpServer {
    public:
        TcpServer(const std::string &ip, const std::string &port);
        ~TcpServer();

        CLIENT_DATA_STATE hasDataToRead(std::shared_ptr<asio::ip::tcp::socket> client);

        std::shared_ptr<asio::ip::tcp::socket> accept();
        std::vector<char> receive(std::shared_ptr<asio::ip::tcp::socket> client);
        void send(std::shared_ptr<asio::ip::tcp::socket> client, const std::vector<char> &message);
        std::map<std::shared_ptr<asio::ip::tcp::socket>, std::string> _clients;

    private:
        asio::io_service _io_service;
        asio::ip::tcp::endpoint _endpoint;
        asio::ip::tcp::acceptor _acceptor;
};

#endif /* !TCPSERVER_HPP_ */
