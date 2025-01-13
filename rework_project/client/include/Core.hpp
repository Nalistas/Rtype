/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Window.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_


class Core {
    public:
        Core();
        ~Core();

        void run(void);

    private:
        raylib::Window _window;

};

#endif /* !CORE_HPP_ */
