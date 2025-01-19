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
        /**
         * @brief Construct a new Udp Client object
         * @param ip the ip of the server
         * @param port the port of the server
         */
        UdpClient(const std::string &ip, const std::string &port);


        /**
         * @brief Construct a new Udp Client object
         */
        UdpClient();

        /**
         * @brief Destroy the Udp Client object
         */
        ~UdpClient();

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

        /**
         * @brief Set the Server object
         * @param ip the ip of the server
         * @param port the port of the server
         */
        void setServer(const std::string &ip, const std::string &port);


    private:
        asio::io_service _io_service;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::resolver::results_type _results;
};

#endif /* !UDPCLIENT_HPP_ */
