/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TCPPROTOCOL
*/

#include "Client.hpp"
#include "IGame.hpp"
#include "TcpServer.hpp"
#include "Room.hpp"
#include <memory>
#include <map>
#include <functional>

#ifndef TCPPROTOCOL_HPP_
    #define TCPPROTOCOL_HPP_

class TcpProtocol {
    public:

        enum INSTRUCTIONS_SERVER_TO_CLIENT {
            OK = 200,
            KO = 201,
            ROOM_UPDATE = 1,
            // SET_READY = 2,
            LOAD_SPRITE = 3,
            LOAD_BACKGROUND = 4,
            LOAD_MUSIC = 5,
            LOAD_ACTION = 6,
            START_GAME = 7
        };

        enum INSTRUCTIONS_CLIENT_TO_SERVER {
            SET_NAME = 1,
            ENTER_ROOM = 2,
            LEAVE_ROOM = 4,
            MISSING_FILE = 6,
            CREATE_ROOM = 7,
            LIST_ROOMS = 8,
            DELETE_ROOM = 9,
            SET_READY = 10
        };

        /**
         * @brief Construct a new TcpProtocol object
         * 
         * @param rooms Reference to a map of room IDs and Room objects
         * @param clients Reference to a map of client sockets and Client objects
         * @param tcpServer Reference to a TcpServer object
         * @param launchGame Pointer to a function that launches a game
         */
        TcpProtocol(
            std::map<uint8_t, Room> &rooms,
            std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &clients,
            TcpServer &tcpServer,
            std::function<void(uint8_t roomId)> launchGame
        );

        /**
         * @brief Destroy the TcpProtocol object
         * 
         */
        ~TcpProtocol();

        /**
         * @brief Treat a client command
         * 
         * @param client The client socket
         * @param params The command parameters
         * @return int 0 if success, -1 if error
         * 
         */
        int interpreter(std::shared_ptr<asio::ip::tcp::socket> &client, std::vector<uint8_t> data);

        /**
         * @brief List the rooms for a client
         * 
         * @param client The client socket
         */
        void listRooms(std::shared_ptr<asio::ip::tcp::socket> &client);

        /**
         * @brief Enter a room for a client
         * 
         * @param client The client socket
         * @param roomId The room ID
         */
        void enterRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId);

        /**
         * @brief Create a room for a client
         * 
         * @param client The client socket
         * @param roomName The room name
         * @param gameName The game name
         */
        void createRoom(std::shared_ptr<asio::ip::tcp::socket> &client, std::string roomName, std::string gameName);

        /**
         * @brief Exit a room for a client
         * 
         * @param client The client socket
         */
        void exitRoom(std::shared_ptr<asio::ip::tcp::socket> &client);

        /**
         * @brief Delete a room for a client
         * 
         * @param client The client socket
         * @param roomId The room ID
         */
        void deleteRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId);

        /**
         * @brief transform an image to binary
         * 
         * @param path the path of the image
         * @return std::vector<uint8_t> the binary image
         */
        std::vector<uint8_t> image_to_binary(const std::string &path);

        /**
         * @brief set the name of a client
         * 
         * @param client The client socket
         * @param name The name
         */
        void setName(std::shared_ptr<asio::ip::tcp::socket> &client, std::string name);

        /**
         * @brief change the status of a client
         * 
         * @param client The client socket
         */
        void changeStatus(std::shared_ptr<asio::ip::tcp::socket> &client);

    private:
        std::unordered_map<uint8_t, std::function<void(std::shared_ptr<asio::ip::tcp::socket> &, std::istringstream&)>> _commandMap;

        std::map<uint8_t, Room> &_rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &_clients;
        TcpServer &_tcpServer;
        std::function<void(uint8_t roomId)> _launchGame;

        void copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value);

};

#endif /* !TCPPROTOCOL_HPP_ */
