/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Window.hpp"
#include "TcpClient.hpp"
#include "ClientRoom.hpp"
#include "RayText.hpp"
#include "Sprite.hpp"
#include "RayMusic.hpp"
#include "Background.hpp"

#include <vector>
#include <list>
#include <map>
#include <array>
#include <functional>

#ifndef CORE_HPP_
    #define CORE_HPP_

    enum INSTRUCTIONS_SERVER_TO_CLIENT {
        OK = 200,
        KO = 201,
        ROOM_UPDATE = 1,
        // SET_READY = 2,
        LOAD_SPRITE = 3,
        LOAD_BACKGROUND = 4,
        LOAD_MUSIC = 5,
        LOAD_ACTION = 6,
        START_GAME = 7,
        DECLARE_GAME = 8,
        LEAVE_ENTER_ROOM = 9
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
 * @brief Core
 */
class Core {
    public:
        /**
         * @brief Construct a new Core object
         * @param ip the ip of the server
         * @param port the port of the server
         * @param username the username of the client
         */
        Core(std::string ip, std::string port, std::string username);

        /**
         * @brief Destroy the Core object
         */
        ~Core();

        void interpretor();

        /**
         * @brief Run the core
         */
        void run(void);

        void drawPopup(bool &showPopup, std::string &roomName, std::string title);

        bool isEltPressed(int x, int y, int width, int height);

        void displayCreateRoomBtn(std::string &roomName, bool &showPopup);

        void manageExitRoom();

        void setRoom(int roomId);

        void roomUpdate(std::vector<uint8_t> tcpResponse);

        void leaveEnterRoom(std::vector<uint8_t> tcpResponse);

        void save_image(const std::string &path, const std::vector<char> &buffer);

        void load_sprite(std::vector<uint8_t> tcpResponse);

        void load_background(std::vector<uint8_t> tcpResponse);

        void load_music(std::vector<uint8_t> tcpResponse);

        void load_action(std::vector<uint8_t> tcpResponse);

        void checkIfFileExist(std::string path);
    private:
        raylib::Window _window;
        TcpClient _tcpClient;
        std::vector<ClientRoom> _rooms;
        std::list<std::string> _games;
        std::map<uint8_t, ClientRoom> _roomsMap;
        std::vector<std::pair<std::string, std::function<void()>>> _commandQueue;
        std::map<raylib::RayText, std::function<void()>> _buttons_room;
        std::map<INSTRUCTIONS_SERVER_TO_CLIENT, std::function<void(std::vector<uint8_t>)>> _instructions;
        std::vector<std::string> _gameList;
        std::vector<raylib::Sprite> _sprites;
        std::vector<Background> _backgrounds;
        std::vector<raylib::RayMusic> _musics;
        // [0][Key] = Key released
        // [1][Key] = Key pressed

        // pk 2 ??? c'est pas mieux de faire un vecteur ?? Ambroise
        std::array<std::map<uint32_t, std::function<void(void)>>, 2> _actions;

        int _roomId;
        bool _startGame;
};

#endif /* !CORE_HPP_ */
