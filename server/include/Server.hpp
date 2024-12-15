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
#include <memory>
#include "registry.hpp"
#include "AsioApi.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"

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
    REMOVE = 2,
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
        void broadcastDelete(ecs::entity entity);
        void broadcast(char op_code, char entity_type, ecs::entity const &entity_id, std::vector<char> const &data);
        void broadcastCreate(ecs::entity entity);
        void broadcastUpdate(ecs::entity entity);

        void setNewClient(udp::endpoint const &endpoint);

        void sendToClient(std::size_t id, std::vector<char> const &data);

        void set_actions(std::vector<rtype::ClientAction> &actions);
        void updateScreen(std::size_t id_client);

    private:

        std::size_t _time;

        std::vector<std::unique_ptr<rtype::IClientActionHandler>> _handlers;

        ///                                key, pressed -> id action
        std::unordered_map<std::size_t, std::pair<std::size_t, bool>> _keys; 


        DLLdr::DLLoader<rtype::IGame> _dll;
        std::unique_ptr<rtype::IGame> _game;

        std::shared_ptr<ecs::registry> _registry;
        // ecs::registry _registry;
        rtype_protocol::AsioApi _api;
        std::unordered_map<udp::endpoint, std::size_t, endpoint_hash_class> _clients;
        std::unordered_map<std::size_t, udp::endpoint> _reverse_clients;
};

#endif /* !SERVER_HPP_ */
