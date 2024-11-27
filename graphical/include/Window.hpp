/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Window
*/

#include <list>
#include <string>
#include "raylib.h"

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

namespace raylib {

class Window {
    public:
        Window(unsigned int width = 500, unsigned int height = 500);
        ~Window();

        /**
         * @brief Set the fps of the window
         */
        void set_fps(unsigned int fps);

        /**
         * @brief Close the window
         */
        void close();

        /**
         * @brief Resize the window
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * @brief Get the keys pressed
         */
        std::list<int> get_keys() const;

        /**
         * @brief Start the drawing
         */
        void start_drawing();

        /**
         * @brief End the drawing
         */
        void end_drawing();

        /**
         * @brief Clear the window
         */
        void clear(Color color = WHITE);

        /**
         * @brief Set the title of the window
         */
        void set_title(std::string const &title);

        /**
         * @brief Check if the window is running
         */
        bool is_running() const;

        /**
         * @brief Get the size of the window
         */
        std::pair<unsigned int, unsigned int> get_size() const;

        /**
         * @brief Draw a string
         */
        void draw_text(std::string const &text, int x, int y, int fontSize, Color color);

        /**
         * @brief Draw a rectangle
         */
        void draw_rectangle(int x, int y, int width, int height, Color color);




    private:
        bool _running;
        unsigned int _width;
        unsigned int _height;
        unsigned int _fps;
};

}

#endif /* !WINDOW_HPP_ */
