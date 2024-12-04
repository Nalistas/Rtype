/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GraphicalCore
*/

#include "raylib.h"
#include "Raylib/AudioDevice.hpp"
#include "Raylib/Window.hpp"
#include "Raylib/Sprite.hpp"
#include "Raylib/RayMusic.hpp"

#include <list>


#ifndef GRAPHICALCORE_HPP_
    #define GRAPHICALCORE_HPP_


/**
 * @brief GraphicalCore class, this handle the basics of 2d graphics, window, music and background
 */
class GraphicalCore {
    public:
        /**
         * @brief Construct a new GraphicalCore object
         */
        GraphicalCore();

        /**
         * @brief Destroy the GraphicalCore object
         */
        ~GraphicalCore();

        /**
         * this function start the iteration for music and background, it will call the BeginDrawing() raylib function
         */
        void start_draw(void);

        /**
         * this function stop the iteration for music and background, it will call the EndDrawing() raylib function
         */
        void stop_draw(void);

        /**
         * this function add a background to the list of background
         * @param path the path to the background file
         * @param position the position of the background
         */
        void insertBackground(std::string const &path, std::size_t position = 0);

        raylib::Window &getWindow();
        raylib::AudioDevice &getAudioDevice();
        raylib::RayMusic &getMusic();

    protected:
        raylib::RayMusic _music;
        raylib::Window _window;
        raylib::AudioDevice _audio_device;

        std::list<raylib::Sprite> _background;
};

#endif /* !GRAPHICALCORE_HPP_ */
