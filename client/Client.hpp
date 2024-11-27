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
        Client(const std::string &hostname);
        ~Client();
        void send_message(const std::string &message);  // Nouvelle méthode pour envoyer des messages
        int loop();

    private:
        asio::io_context io_context;
        udp::resolver resolver;
        udp::endpoint endpoint;
        udp::socket socket;
};

#endif /* !CLIENT_HPP_ */
