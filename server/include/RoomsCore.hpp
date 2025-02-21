/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include <string>
#include <map>
#include <unordered_map>
#include "TcpServer.hpp"
#include "TcpProtocol.hpp"
#include "Room.hpp"
#include "Client.hpp"
#include "RessourcesManager.hpp"
#include "DLLoader.hpp"
#include "SafeDirectoryLister.hpp"
#include "Process.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_

/**
 * @brief The core of the rooms server
 * This class is used to manage the rooms server
 * It will manage the rooms, the clients, the games and the ressources
 */
class RoomsCore {
    public:
        /**
         * @brief Construct a new Rooms Core object
         * @param port the port of the server
         */
        RoomsCore(std::string const &executable_name, std::string const &port, bool &running);

        /**
         * @brief Destroy the Rooms Core object
         */
        ~RoomsCore();

        /**
         * @brief Run the rooms core
         */
        void run(void);

        /**
         * @brief Launch a game
         * @param roomId the id of the room
         */
        void setGameToLaunch(uint8_t roomId);

        /**
         * @brief Stop the rooms core
         */
        void stop(void);

    private:
        /**
         * @brief Check if there are new clients
         */
        void checkNewClients(void);

        /**
         * @brief Check if there are new clients
         */
        void checkClients(TcpProtocol &tcpProtocol);

        /**
         * @brief Treat a client command
         */
        void treatClient(std::shared_ptr<asio::ip::tcp::socket> &client, TcpProtocol &tcpProtocol);

        /**
         * @brief Launch a game
         */
        void launchGame();

        /**
         * @brief extract all the ressources from the games
         */
        void setGamesRessources(void);

        /**
         * @brief find an available port
         * @param start_port the port to start the search
         * @return the available port
         */
        int find_available_port(unsigned short start_port);

        /**
         * @brief send the game ressources to the clients
         * @param port the port of the client
         * @param game the game name
         */
        void sendGameRessourcesToTheRoom(std::string game, const uint8_t room);

        /**
         * @brief get the clients of a room
         * @param room the room id
         * @return the clients of the room
         */
        std::list<std::pair<std::shared_ptr<asio::ip::tcp::socket>, Client>> getClients(const uint8_t room);

        /**
         * @brief get the local ip
         * @return the local ip
         */
        std::vector<uint8_t> get_local_ip();

        /**
         * @brief get the client id
         * @param room the room id
         * @param client the client socket
         * @return the client id
         */
        int getClientId(const uint8_t room, const std::shared_ptr<asio::ip::tcp::socket> &clientt);


        TcpServer _tcpServer;
        std::map<uint8_t, Room> _rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> _clients;

        std::map<uint8_t, Room> _roomsToLaunch;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> _clientsToLaunch;

        std::vector<std::string> _gameList;
        std::unordered_map<std::string, RessourcesManager> _ressources;
        std::unordered_map<std::string, std::string> _gameNameToPath;
        process::Process _my_process;
        std::string _executable_name;

        bool &_run;
};

#endif /* !CORE_HPP_ */
