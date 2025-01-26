/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Login
*/

#include <string>
#include <array>
#include "Window.hpp"
#include "RayText.hpp"  // Add this line if it's missing

#ifndef LOGIN_HPP_
    #define LOGIN_HPP_

/**
 * @brief Login class to handle the login window
 */
class Login {
    public:
        Login();
        ~Login();

        /**
         * @brief Run the login window
         * @return true if the login is successful, false otherwise
         */
        bool run();

        /**
         * @brief Get the ip
         * @return the ip
         */
        std::string get_ip() const;

        /**
         * @brief Get the port
         * @return the port
         */
        std::string get_port() const;

        /**
         * @brief Get the username
         * @return the username
         */
        std::string get_username() const;

    private:

        enum InputType {
            USERNAME = 0,
            IP = 1,
            PORT = 2
        };

        /**
         * @brief Handle the input on the client
         */
        void handleInput(void);

        int focus;
        raylib::Window _window;
        bool _is_running;
        std::array<raylib::RayText, 5> _titles;
        std::array<raylib::RayText, 3> _inputs;
};

#endif /* !LOGIN_HPP_ */
