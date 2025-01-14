/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Window.hpp"

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

        /**
         * @brief Run the core
         */
        void run(void);

    private:
        raylib::Window _window;

};

#endif /* !CORE_HPP_ */
