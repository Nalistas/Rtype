/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <asio.hpp>

using asio::ip::udp;

class Client {
    public:

        /**
         * @brief Construct a new Client object
         */
        Client();

        /**
         * @brief Destroy the Client object
         */
        ~Client();

        /**
         * @brief Send a message to the server
         */
        void send_message(const std::string &message);

        /**
         * @brief Connect to the server
         */
        bool connect(const std::string &ip, const std::string &port = "5000");

        /**
         * @brief Get the data from the server
         */
        std::string get_data();

        /**
         * @brief Check if the client has data to read
         */
        bool has_data();


    private:
        asio::io_context io_context;
        udp::resolver resolver;
        udp::endpoint endpoint;
        udp::socket socket;
        bool connected;
};

#endif /* !CLIENT_HPP_ */
