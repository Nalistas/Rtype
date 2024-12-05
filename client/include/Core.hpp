/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include "registry.hpp"
#include "Raylib/Window.hpp"
#include "Raylib/AudioDevice.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_

class Core {
    public:
        Core(std::size_t win_width, std::size_t win_height);
        ~Core();

        int run(void);

    private:
        raylib::Window _window;
        raylib::AudioDevice audioDevice;
        ecs::registry _registry;

        std::size_t time;
};

#endif /* !CORE_HPP_ */
