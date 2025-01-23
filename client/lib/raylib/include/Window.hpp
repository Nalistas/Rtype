/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Window
*/

#include <list>
#include <string>
#include <cstdint>

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

namespace raylib {
#include "raylib.h"

/**
 * @brief Window class to handle the window
 */
class Window {
    public:

        /**
         * @brief The state of the keys
         * @details RELEASED, PRESSED, DOWN, UP.
         * - RELEASED: The key is not pressed anymore, its value is 0
         * - PRESSED: The key is pressed, its value is 1
         * - DOWN: The key is pressed and down, its value is 2
         * - UP: The key is pressed and up, its value is 3
         */
        enum BUTTON_STATE {
            RELEASED    = 0,
            PRESSED     = 1,
            DOWN        = 2,
            UP          = 3
        };

        /**
         * @brief Construct a new Window object
         * @param width the width of the window, by default 500
         * @param height the height of the window, by default 500
         */
        Window(unsigned int width = 500, unsigned int height = 500);

        /**
         * @brief destructor of the window
         */
        ~Window();

        /**
         * @brief Set the fps of the window
         * @param fps the new fps
         */
        void set_fps(unsigned int fps);

        /**
         * @brief Close the window by setting _running to false
         */
        void close();

        /**
         * @brief Resize the window
         * @param width the new width of the window
         * @param height the new height of the window
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * @brief Get the keys in the state defined in the parameter
         * @param state the state of the keys, based on the enum ecs::Window::BUTTON_STATE, by defauld, it is pressed
         * @return a list of keys
         * @note the int inside correspond to the key corresponding in the enum of raylib, see the raylib documentation
         */
        std::list<int> get_keys(BUTTON_STATE state = BUTTON_STATE::PRESSED) const;


        /**
         * @brief Get the mouse position
         * @return the mouse position using the function GetMousePosition from raylib
         */
        Vector2 get_mouse_position() const;

        /**
         * @brief Get the mouse button in the state defined in the parameter
         * @param state the state of the keys, based on the enum ecs::Window::BUTTON_STATE, by defauld, it is pressed
         * @return a list of mouse buttons, the list is empty if no button is pressed
         * @note the int inside correspond to the mouse button corresponding in the enum of raylib, see the raylib documentation
         */
        std::list<int> get_mouse_buttons(BUTTON_STATE state = BUTTON_STATE::PRESSED) const;

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
        void clear(Color color) {ClearBackground(color);}

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
        void draw_text(std::string const &text, int x, int y, int fontSize, Color color) { DrawText(text.c_str(), x, y, fontSize, color); }

        /**
         * @brief Draw a rectangle
         */
        void draw_rectangle(int x, int y, int width, int height, Color color) { DrawRectangle(x, y, width, height, color); }

        /**
         * @brief Check if a key is in the state defined in the parameter
         * @param state the state of the keys, based on the enum ecs::Window::BUTTON_STATE
         * @param key the key to check, see the raylib documentation
         * @return true if the key is in the state defined in the parameter, false otherwise
         */
        bool is_key(BUTTON_STATE state, int key) const;

        /**
         * @brief Check if a mouse button is in the state defined in the parameter
         * @param state the state of the mouse buttons, based on the enum ecs::Window::BUTTON_STATE
         * @param button the mouse button to check, see the raylib documentation
         * @return true if the mouse button is in the state defined in the parameter, false otherwise
         */
        bool is_mouse_button(BUTTON_STATE state, int button) const;

        /**
         * @brief Get the character pressed, this function only works if the key is a letter
         */
        uint8_t get_char_pressed() const;

        /**
         * @brief Get the ascii value of the key. This function follow the raylib documentation
         * @note it only goes from 32 to 126, the printable characters
         */
        uint8_t get_char_from_enum(int key) const;

    private:
        bool _running;
        unsigned int _width;
        unsigned int _height;
        unsigned int _fps;
};

}

#endif /* !WINDOW_HPP_ */
