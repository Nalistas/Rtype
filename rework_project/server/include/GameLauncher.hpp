/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameLauncher
*/

#include <string>
#include <list>
#include <vector>

#include "DLLoader.hpp"
#include "IGame.hpp"
#include "UdpServer.hpp"
#include "GameCore.hpp"
#include "ClientActionLog.hpp"

#ifndef GAMELAUNCHER_HPP_
    #define GAMELAUNCHER_HPP_


class GameLauncher {
    public:
        struct Player {
            std::string name;
            std::string ip;
        };

        GameLauncher(std::string const &game_path);
        ~GameLauncher();

        std::list<std::vector<char>> const &getRessources();

        std::string getIp();

        uint16_t getPort();

        void launch(std::list<Player> const &players);

        GameCore::ServerActions getServerActions();

    private:
        std::unique_ptr<rtype::IGame> _game;
        DLLdr::DLLoader<rtype::IGame> _loader;
        std::list<std::vector<char>> _ressources;
        ecs::registry _registry;
        std::unordered_map<std::string, std::size_t> _players;
        std::unique_ptr<ClientActionLog> _client_action_log;

        std::vector<std::shared_ptr<rtype::IClientActionHandler>> _handlers;

        UdpServer _server;
};

#endif /* !GAMELAUNCHER_HPP_ */
