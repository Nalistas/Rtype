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

        /**
         * @brief Construct a new Tcp Server object
         * @param ip the ip of the server
         * @param port the port of the server
         */
        TcpServer(const std::string &ip, const std::string &port);

        /**
         * @brief Destroy the Tcp Server object
         */
        ~TcpServer();

        /**
         * @brief Check if the client has data to read
         * @param client the client socket
         * @return CLIENT_DATA_STATE, the state of the client with {EMPTY = 0, DATA = 1, DISCONNECTED = 2, CLIENT_ERROR = 3}
         */
        CLIENT_DATA_STATE hasDataToRead(std::shared_ptr<asio::ip::tcp::socket> client);

        /**
         * @brief Accept a client
         * @return std::shared_ptr<asio::ip::tcp::socket> the client socket
         */
        std::shared_ptr<asio::ip::tcp::socket> accept();

        /**
         * @brief Receive data from a client
         * @param client the client socket
         * @return std::vector<uint8_t> the data received
         */
        std::vector<uint8_t> receive(std::shared_ptr<asio::ip::tcp::socket> client);

        /**
         * @brief Send data to a client
         * @param client the client socket
         * @param message the message to send
         */
        void send(std::shared_ptr<asio::ip::tcp::socket> client, const std::vector<uint8_t> &message);

    private:
        asio::io_service _io_service;
        asio::ip::tcp::endpoint _endpoint;
        asio::ip::tcp::acceptor _acceptor;
};

#endif /* !TCPSERVER_HPP_ */
