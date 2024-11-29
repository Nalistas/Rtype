#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <unordered_map>
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

        // List of clients (key = endpoint, value = name)
        std::unordered_map<udp::endpoint, std::string, std::hash<std::string>> clients;
};

#endif /* !SERVER_HPP_ */
