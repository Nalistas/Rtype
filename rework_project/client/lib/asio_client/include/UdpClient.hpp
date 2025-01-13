/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
    #define UDPCLIENT_HPP_

#include <asio.hpp>
#include <string>
#include <vector>

class UdpClient {
    public:
        UdpClient(const std::string &ip, const std::string &port);
        ~UdpClient();

        void send(const std::vector<uint8_t> &message);
        std::vector<uint8_t> receive();
        bool hasData();

    private:
        asio::io_service _io_service;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::resolver::results_type _results;
};

#endif /* !UDPCLIENT_HPP_ */
