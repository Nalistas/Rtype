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
    this->clear({255, 255, 255, 255});
}

void raylib::Window::end_drawing()
{
    EndDrawing();
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

void raylib::Window::draw_text(std::string const &text, int x, int y, int fontSize)
{
    DrawText(text.c_str(), x, y, fontSize, BLACK);
}

void raylib::Window::draw_rectangle(int x, int y, int width, int height, Color color)
{
    DrawRectangle(x, y, width, height, color);
}

bool raylib::Window::is_key(BUTTON_STATE state, int key) const
{
    switch (state) {
        case RELEASED:
            return IsKeyReleased(key);
        case PRESSED:
            return IsKeyPressed(key);
        case DOWN:
            return IsKeyDown(key);
        case UP:
            return IsKeyUp(key);
        default:
            return false;
    }
}

bool raylib::Window::is_mouse_button(BUTTON_STATE state, int button) const
{
    switch (state) {
        case RELEASED:
            return IsMouseButtonReleased(button);
        case PRESSED:
            return IsMouseButtonPressed(button);
        case DOWN:
            return IsMouseButtonDown(button);
        case UP:
            return IsMouseButtonUp(button);
        default:
            return false;
    }
}

uint8_t raylib::Window::get_char_pressed() const
{
    return static_cast<uint8_t>(GetCharPressed());
}

uint8_t raylib::Window::get_char_from_enum(int key) const
{
    if (key < 32 || key > 126)
        return 0;
    return static_cast<uint8_t>(key);
}

