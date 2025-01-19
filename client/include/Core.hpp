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
#include "UdpClient.hpp"

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
        LOAD_SPRITE = 3,
        LOAD_BACKGROUND = 4,
        LOAD_MUSIC = 5,
        LOAD_ACTION = 6,
        START_GAME = 7,
        DECLARE_GAME = 8,
        LEAVE_ENTER_ROOM = 9,
        FORCE_REGISTER_IN_ROOM = 10
    };

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

        void drawPopup(bool &showPopup, std::vector<raylib::RayText> &inputs, int &focus);

        bool isEltPressed(int x, int y, int width, int height);

        // void displayCreateRoomBtn(std::string &roomName, bool &showPopup);

        void manageExitRoom();

        void setRoom(uint8_t roomId);

        void roomUpdate(std::vector<uint8_t> tcpResponse);

        void leaveEnterRoom(std::vector<uint8_t> tcpResponse);

        void save_image(const std::string &path, const std::vector<char> &buffer);

        void load_sprite(std::vector<uint8_t> tcpResponse);

        void load_background(std::vector<uint8_t> tcpResponse);

        void load_music(std::vector<uint8_t> tcpResponse);

        void load_action(std::vector<uint8_t> tcpResponse);

        void checkIfFileExist(std::string path);

        void forceInRoom(std::vector<uint8_t> tcpResponse);

        void manageGetReady();
    private:
        raylib::Window _window;
        TcpClient _tcpClient;
        UdpClient _udpClient;
        std::vector<ClientRoom> _rooms;
        std::list<std::string> _games;
        // std::map<uint8_t, ClientRoom> _roomsMap;
        std::vector<std::pair<std::string, std::function<void(std::vector<uint8_t>)>>> _commandQueue;
        std::map<raylib::RayText, std::function<void()>> _buttons_room;
        std::vector<raylib::RayText> _texts_room;
        std::map<INSTRUCTIONS_SERVER_TO_CLIENT, std::function<void(std::vector<uint8_t>)>> _instructions;
        std::vector<std::string> _gameList;
        std::map<uint32_t, raylib::Sprite> _sprites;
        std::map<uint32_t, Background> _backgrounds;
        std::map<uint32_t, raylib::RayMusic> _musics;

        // [0][Key] = Key released
        // [1][Key] = Key pressed
        std::array<std::map<uint32_t, uint32_t>, 2> _actions;

        uint8_t _roomId;
        bool _startGame;
};

#endif /* !CORE_HPP_ */
