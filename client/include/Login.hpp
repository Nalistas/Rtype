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

class Login {
    public:
        Login();
        ~Login();

        bool run();

        std::string get_ip() const;
        std::string get_port() const;
        std::string get_username() const;

    private:

        enum InputType {
            USERNAME = 0,
            IP = 1,
            PORT = 2
        };

        void handleInput(void);

        int focus;
        raylib::Window _window;
        bool _is_running;
        std::array<raylib::RayText, 4> _titles;
        std::array<raylib::RayText, 3> _inputs;
};

#endif /* !LOGIN_HPP_ */
