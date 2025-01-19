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


/**
 * @brief The GameLauncher class
 * this class allows to launch a game. It is a wrapper around the GameCore class.
 * It open the game (dynamic library), extract all the ressources and launch the game
 * It also launch the UDP server. It is the transition between the TCP server and the UDP server
 */

class GameLauncher {
    public:
        struct Player {
            std::string name;
            std::string ip;
        };

        /**
         * @brief Construct a new Game Launcher object
         * @param game_path the path to the game executable, which is a shared library
         */
        GameLauncher(std::string const &game_path, int port);

        /**
         * @brief Destroy the Game Launcher object
         */
        ~GameLauncher();

        /**
         * @brief Get the Ressources object
         * @return std::list<std::vector<uint8_t>> const&, the list of ressources already ready to be sent to the clients
         */
        std::list<std::vector<uint8_t>> const &getRessources();

        /**
         * @brief Get the Ip object
         * @return std::string, the ip of the server
         */
        std::string getIp();

        /**
         * @brief Get the Port object
         * @return uint16_t, the port of the server
         */
        uint16_t getPort();

        /**
         * @brief Launch the game
         * @param players the list of players
         */
        void launch();

        /**
         * @brief Get the Server Actions object
         * @return GameCore::ServerActions, the list of functions to be executed
         */
        GameCore::ServerActions getServerActions(void);


        void speedUpdater(std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y);

        void positionUpdater(std::size_t player_id, std::size_t e_id, int x, int y);

        void creater(std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y);

        void Deleter(std::size_t player_id, std::size_t e_id);

        void BackgroundChanger(std::size_t client_id, std::size_t background_id);

        void MusicChanger(std::size_t client_id, std::size_t music_id);

    private:
        std::unique_ptr<rtype::IGame> _game;
        DLLdr::DLLoader<rtype::IGame> _loader;
        std::list<std::vector<uint8_t>> _ressources;
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_map<std::string, std::size_t> _players;
        std::unordered_map<std::size_t, asio::ip::udp::endpoint> _players_endpoints;
        std::unique_ptr<ClientActionLog> _client_action_log;

        std::vector<std::shared_ptr<rtype::IClientActionHandler>> _handlers;

        UdpServer _server;
};

#endif /* !GAMELAUNCHER_HPP_ */
