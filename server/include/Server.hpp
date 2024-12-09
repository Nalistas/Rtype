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

enum class EntityOperation {
    CREATE = 1,
    DELETE = 2,
    UPDATE = 3
};

enum class EntityType {
    BACKGROUND = 1,
    MUSIC = 2,
    SOUND = 3,
    SPRITE = 4
};

struct endpoint_hash_class {
    std::size_t operator()(const udp::endpoint &ep) const;
};

class Server {
    public:
        Server();
        ~Server();
        int loop();
        void send_create_entity(udp::endpoint client_endpoint, EntityType entity_type, int entity_id, const std::string& entity_data);
        void send_delete_entity(udp::endpoint client_endpoint, int entity_id);
        void send_update_entity(udp::endpoint client_endpoint, EntityType entity_type, int entity_id, const std::string& updated_data);
        void handle_receive(const std::string& message);

    private:
        void start_receive();

        asio::io_context io_context;
        udp::socket socket;
        udp::endpoint sender_endpoint_;
        std::array<char, 1024> recv_buffer;

        std::unordered_set<udp::endpoint, endpoint_hash_class> clients;
};

#endif /* !SERVER_HPP_ */
