/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Window
*/

#include "raylib.h"
#include "Window.hpp"

#include <list>
#include <functional>

raylib::Window::Window(unsigned int width, unsigned int height) :
    _running(true), _width(width), _height(height), _fps(60)
{
    InitWindow(width, height, "rtype");
    SetTargetFPS(_fps);
}

raylib::Window::~Window()
{
    CloseWindow();
}

void raylib::Window::close()
{
    _running = false;
}

void raylib::Window::resize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    SetWindowSize(width, height);
}

void raylib::Window::set_fps(unsigned int fps)
{
    this->_fps = fps;
    SetTargetFPS(fps);
}

std::list<int> raylib::Window::get_keys(BUTTON_STATE state) const
{
    std::list<int> keys;

    std::function<bool(int)> fct;

    switch (state) {
        case RELEASED:
            fct = IsKeyReleased;
            break;
        case PRESSED:
            fct = IsKeyPressed;
            break;
        case DOWN:
            fct = IsKeyDown;
            break;
        case UP:
            fct = IsKeyUp;
            break;
        default:
            return keys;
    }

    for (int i = 0; i < 348; i++) {
        if (fct(i))
            keys.push_back(i);
    }
    return keys;
}

Vector2 raylib::Window::get_mouse_position() const
{
    return GetMousePosition();
}

std::list<int> raylib::Window::get_mouse_buttons(BUTTON_STATE state) const
{
    std::list<int> buttons;

    std::function<bool(int)> fct;

    switch (state) {
        case RELEASED:
            fct = IsMouseButtonReleased;
            break;
        case PRESSED:
            fct = IsMouseButtonPressed;
            break;
        case DOWN:
            fct = IsMouseButtonDown;
            break;
        case UP:
            fct = IsMouseButtonUp;
            break;
        default:
            return buttons;
    }

    for (int i = 0; i < 7; i++) {
        if (fct(i))
            buttons.push_back(i);
    }
    return buttons;
}

void raylib::Window::start_drawing()
{
    BeginDrawing();
}

void raylib::Window::end_drawing()
{
    EndDrawing();
}

void raylib::Window::clear(Color color)
{
    ClearBackground(color);
}

void raylib::Window::set_title(std::string const &title)
{
    SetWindowTitle(title.c_str());
}

bool raylib::Window::is_running() const
{
    return _running && !WindowShouldClose();
}

std::pair<unsigned int, unsigned int> raylib::Window::get_size() const
{
    return std::make_pair(_width, _height);
}

void raylib::Window::draw_text(std::string const &text, int x, int y, int fontSize, Color color)
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

void raylib::Window::draw_rectangle(int x, int y, int width, int height, Color color)
{
    DrawRectangle(x, y, width, height, color);
}


