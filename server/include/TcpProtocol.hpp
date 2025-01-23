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

/**
 * @brief The TcpProtocol class
 * This class is used to interpret the commands sent by the clients
 * It will then call the appropriate function to treat the command
 */
class TcpProtocol {
    public:

        /**
         * @brief Enum of the instructions from the server to the client
         */
        enum INSTRUCTIONS_SERVER_TO_CLIENT {
            OK = 200,
            KO = 201,
            ROOM_UPDATE = 1,
            LOAD_SPRITE = 3,
            LOAD_BACKGROUND = 4,
            LOAD_MUSIC = 5,
            LOAD_ACTION = 6,
            START_GAME = 7,
            DECLARE_GAME = 8,
            LEAVE_ENTER_ROOM = 9,
            FORCE_REGISTER_IN_ROOM = 10
        };

        /**
         * @brief Enum of the instructions from the client to the server
         */
        enum INSTRUCTIONS_CLIENT_TO_SERVER {
            SET_NAME = 1,
            ENTER_ROOM = 2,
            LEAVE_ROOM = 4,
            LIST_GAMES = 5,
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
         * @param gameList Reference to a vector with the name of the games
         */
        TcpProtocol(
            std::map<uint8_t, Room> &rooms,
            std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &clients,
            TcpServer &tcpServer,
            std::function<void(uint8_t roomId)> launchGame,
            std::vector<std::string> &gameList
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

        /**
         * @brief send all the available games to a client
         */
        void listGames(std::shared_ptr<asio::ip::tcp::socket> &client);

        /**
         * @brief check if a room is empty
         * @param roomId the id of the room
         * @return the first client found that is still in the room, nullptr if the room is empty
         */
        std::shared_ptr<asio::ip::tcp::socket> isRoomEmpty(uint8_t roomId);

        /**
         * @brief format the launch room command to all clients in the room
         * 
         * @param roomId the id of the room
         */
        std::vector<uint8_t> formatLaunchRoom(uint8_t roomId);

        /**
         * @brief format the room update command to all clients in the room
         * 
         * @param roomId the id of the room
         * @param created true if the room was created, false if it was destroyed
         */
        std::vector<uint8_t> formatRoomCreatedDeleted(uint8_t roomId, bool created);

        /**
         * @brief format the game available command to a client
         * 
         * @param roomId the id of the room
         */
        std::vector<uint8_t> formatGameAvailable(uint8_t roomId);

        /**
         * @brief format the player room update command to all clients in the room
         * 
         * @param roomId the id of the room
         * @param enter true if the player entered the room, false if he left it
         * @param name the name of the player
         */
        std::vector<uint8_t> formatPlayerRoomUpdate(uint8_t roomId, bool enter, std::string const &name);

        /**
         * @brief format the ok command to a client
         * 
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> formatOk();

        /**
         * @brief format the ko command to a client
         * 
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> formatKo();

        /**
         * @brief format the force register in a room command to a client
         * 
         * @param roomId the id of the room
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> formatForceRegisterInRoom(uint8_t roomId);

    private:
        std::unordered_map<uint8_t, std::function<void(std::shared_ptr<asio::ip::tcp::socket> &, std::istringstream&)>> _commandMap;

        std::map<uint8_t, Room> &_rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &_clients;
        TcpServer &_tcpServer;
        std::function<void(uint8_t roomId)> _launchGame;
        std::vector<std::string> &_gameList;

        /**
         * @brief copy a uint32_t to a vector of uint8_t
         * 
         * @param vec the vector
         * @param pos the position
         * @param value the value
         */
        void copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value);

};

#endif /* !TCPPROTOCOL_HPP_ */
