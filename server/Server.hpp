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
#include <unordered_set>

using asio::ip::udp;

namespace std {
    template <>
    struct hash<udp::endpoint>
    {
        std::size_t operator()(const udp::endpoint& endpoint) const noexcept
        {
            return hash<std::string>()(endpoint.address().to_string()) ^ hash<unsigned short>()(endpoint.port());
        }
    };
}

class Server {
    public:
        Server();
        ~Server();
        int loop();
        void send_create_entity(udp::endpoint client_endpoint, int entity_type_id, int entity_id, const std::string& entity_data);
        void send_delete_entity(udp::endpoint client_endpoint, int entity_id);
        void send_update_entity(udp::endpoint client_endpoint, int entity_id, const std::string& updated_data);
        void handle_receive(const std::string& message);
        void send_background(const udp::endpoint& client_endpoint);

    private:
        void start_receive();

        asio::io_context io_context;
        udp::socket socket;
        udp::endpoint sender_endpoint_;
        std::array<char, 1024> recv_buffer;
        std::unordered_set<udp::endpoint> clients;
};


#endif /* !SERVER_HPP_ */
