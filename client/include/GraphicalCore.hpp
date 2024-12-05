/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GraphicalCore
*/

#include "raylib.h"
#include "Raylib/AudioDevice.hpp"
#include "Raylib/Window.hpp"
#include "Raylib/RayMusic.hpp"
#include "Background.hpp"


#include <list>
#include <memory>
#include <ctime>


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
        GraphicalCore(std::size_t win_width, std::size_t win_height);

        /**
         * @brief Destroy the GraphicalCore object
         */
        ~GraphicalCore();

        /**
         * @brief start the iteration, by playing music and drawing background, it will call the BeginDrawing() raylib function
         */
        void start_draw(void);

        /**
         * @brief stop the iteration for music and background, it will call the EndDrawing() raylib function
         */
        void stop_draw(void);

        /**
         * @brief add a background to the list of background
         * @param background the background as a rvalue that will be moved within the list with std::move
         * @param position the position of the background
         */
        void insertBackground(Background &&background, std::size_t position = 0);

        /**
         * @brief remove a background from the list of background
         * @param position the position of the background
         */
        void removeBackground(std::size_t position = 0);

        /**
         * @brief clear the list of background
         */
        void clearBackgrounds(void);

        /**
         * @brief set the music of the game
         * @param path the path to the music file
         */
        void setMusic(std::string const &path);

        /**
         * @brief get a background from the list of background
         * @param position the position of the background
         * @return the background
         */
        Background &getBackground(std::size_t position = 0);

        /**
         * @brief get the window
         */
        raylib::Window &getWindow();

        /**
         * @brief get the window as a const
         */
        raylib::Window const &getConstWindow() const;

        /**
         * @brief get the music
         */
        std::unique_ptr<raylib::RayMusic> &getMusic();

        /**
         * @brief get the time elapsed since the last update
         */
        float getElapsedTime(void) const;

    protected:
        std::unique_ptr<raylib::RayMusic> _music;
        raylib::Window _window;
        raylib::AudioDevice _audio_device;

        std::list<Background> _backgrounds;
        std::chrono::high_resolution_clock::time_point _last_update;
        float _elapsed;
};

#endif /* !GRAPHICALCORE_HPP_ */
