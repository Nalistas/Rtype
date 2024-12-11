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
#include "../../common/ecs/include/registry.hpp"
#include "Encoder.hpp"
#include "AsioApi.hpp"

using asio::ip::udp;

namespace std {

    /**
     * @brief Hash function for udp::endpoint
     */
    template <>
    struct hash<udp::endpoint>
    {
        std::size_t operator()(const udp::endpoint& endpoint) const noexcept
        {
            return hash<std::string>()(endpoint.address().to_string()) ^ hash<unsigned short>()(endpoint.port());
        }
    };
}

/**
 * @brief Hash function for udp::endpoint
 */
struct endpoint_hash_class {
    std::size_t operator()(const udp::endpoint &ep) const;
};



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

class Server {
    public:
        Server();
        ~Server();
        int loop();

    private:

        ecs::registry _registry;
        rtype_protocol::AsioApi _api;
        rtype_protocol::Encoder _encoder;
        std::unordered_set<udp::endpoint, endpoint_hash_class> _clients;
};

#endif /* !SERVER_HPP_ */
