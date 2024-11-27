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
        Client();
        ~Client();
        int loop();

    private:
        asio::io_context io_context;
        udp::resolver resolver;
        udp::endpoint endpoint;
        udp::socket socket;
};

#endif /* !CLIENT_HPP_ */
