/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

#include <iostream>
#include <unordered_set>
#include <asio.hpp>

using asio::ip::udp;


struct endpoint_hash_class {
    std::size_t operator()(const udp::endpoint &ep) const;
};

class Server {
    public:
        Server();
        ~Server();
        int loop();

    private:
        asio::io_context io_context;
        udp::socket socket;

        // List of clients (key = endpoint, value = name)
        std::unordered_set<udp::endpoint, endpoint_hash_class> clients;
};



#endif /* !SERVER_HPP_ */
