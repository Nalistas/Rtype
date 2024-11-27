/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <asio.hpp>

using asio::ip::udp;

class Server {
    public:
        Server();
        ~Server();
        int loop();

    private:
        asio::io_context io_context;
        udp::socket socket;
};

#endif /* !SERVER_HPP_ */
