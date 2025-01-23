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
         * @brief Launch the game
         * @param players the list of players
         */
        void launch();

        /**
         * @brief Get the Server Actions object
         * @return GameCore::ServerActions, the list of functions to be executed
         */
        GameCore::ServerActions getServerActions(void);

        /**
         * @brief Update the speed of an entity
         *
         * @param player_id the id of the player
         * @param e_id the id of the entity
         * @param speed_x the speed on the x axis
         * @param speed_y the speed on the y axis
         */
        void speedUpdater(std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y);

        /**
         * @brief Update the position of an entity
         *
         * @param player_id the id of the player
         * @param e_id the id of the entity
         * @param x the x position
         * @param y the y position
         */
        void positionUpdater(std::size_t player_id, std::size_t e_id, int x, int y);

        /**
         * @brief Create an entity
         *
         * @param player_id the id of the player
         * @param e_id the id of the entity
         * @param e_g_id the id of the entity in the game
         * @param x the x position
         * @param y the y position
         * @param speed_x the speed on the x axis
         * @param speed_y the speed on the y axis
         */
        void creater(std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y);

        /**
         * @brief Delete an entity
         *
         * @param player_id the id of the player
         * @param e_id the id of the entity
         */
        void Deleter(std::size_t player_id, std::size_t e_id);

        /**
         * @brief Update background of a client
         *
         * @param client_id the id of the client
         * @param background_id the id of the background
         */
        void BackgroundChanger(std::size_t client_id, std::size_t background_id);

        /**
         * @brief Change the music of a client
         *
         * @param client_id the id of the client
         * @param music_id the id of the music
         */
        void MusicChanger(std::size_t client_id, std::size_t music_id);

    private:
        std::unique_ptr<rtype::IGame> _game;
        DLLdr::DLLoader<rtype::IGame> _loader;
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_map<std::string, std::size_t> _players;
        std::unordered_map<std::size_t, asio::ip::udp::endpoint> _players_endpoints;
        std::unique_ptr<ClientActionLog> _client_action_log;

        std::vector<std::shared_ptr<rtype::IClientActionHandler>> _handlers;

        UdpServer _server;
};

#endif /* !GAMELAUNCHER_HPP_ */
