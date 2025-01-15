/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Window.hpp"
#include "TcpClient.hpp"
#include "ClientRoom.hpp"

#include <vector>

#ifndef CORE_HPP_
    #define CORE_HPP_


/**
 * @brief Core
 */
class Core {
    public:
        /**
         * @brief Construct a new Core object
         */
        Core();

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

    private:
        raylib::Window _window;
        TcpClient _tcpClient;
        std::vector<ClientRoom> _rooms;

};

#endif /* !CORE_HPP_ */
