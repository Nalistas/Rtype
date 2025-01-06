/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
    #define TCPCLIENT_HPP_

#include <asio.hpp>
#include <string>
#include <vector>

class TcpClient {
    public:
        TcpClient(const std::string &ip, const std::string &port);
        ~TcpClient();

        void send(const std::vector<char> &message);
        std::vector<char> receive();
        bool hasData();

    private:
        asio::io_service _io_service;
        asio::ip::tcp::socket _socket;
        asio::ip::tcp::resolver::results_type _results;
};

#endif /* !TCPCLIENT_HPP_ */
