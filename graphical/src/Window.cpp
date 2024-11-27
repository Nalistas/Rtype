/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Window
*/

#include "raylib.h"
#include "Window.hpp"

#include <list>

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

std::list<int> raylib::Window::get_keys() const
{
    std::list<int> keys;
    for (int i = 0; i < 348; i++) {
        if (IsKeyDown(i))
            keys.push_back(i);
    }
    return keys;
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


