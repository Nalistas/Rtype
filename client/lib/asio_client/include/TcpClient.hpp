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
        /**
         * @brief Construct a new Tcp Client object
         * @param ip the ip of the server
         * @param port the port of the server
         */
        TcpClient(const std::string &ip, const std::string &port);

        /**
         * @brief Destroy the Tcp Client object
         */
        ~TcpClient();

        /**
         * @brief Send a message to the server
         * @param message the message to send
         */
        void send(const std::vector<uint8_t> &message);

        /**
         * @brief Receive a message from the server
         * @return the message received
         */
        std::vector<uint8_t> receive();

        /**
         * @brief Check if there is data available
         * @return true if there is data available, false otherwise
         */
        bool hasData();

    private:
        asio::io_service _io_service;
        asio::ip::tcp::socket _socket;
        asio::ip::tcp::resolver::results_type _results;
};

#endif /* !TCPCLIENT_HPP_ */
