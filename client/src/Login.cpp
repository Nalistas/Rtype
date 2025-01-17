/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Login
*/

#include "Login.hpp"
#include <array>

Login::Login() :
    focus(0),
    _window(500, 500),
    _is_running(true),
    _titles({
        raylib::RayText("Name:", 10, 10, 30, raylib::BLUE),
        raylib::RayText("Ip   :", 10, 60, 30, raylib::BLUE),
        raylib::RayText("Port:", 10, 110, 30, raylib::BLUE),
        raylib::RayText("Click to connect", 10, 200, 40, raylib::BLACK)
    }),
    _inputs({
        raylib::RayText("", 150, 10 + 50 * 0, 30, raylib::BLACK),
        raylib::RayText("", 150, 10 + 50 * 1, 30, raylib::BLACK),
        raylib::RayText("", 150, 10 + 50 * 2, 30, raylib::BLACK),
    })
{
}

Login::~Login()
{
}

std::string Login::get_ip() const
{
    return _inputs[InputType::IP].getText();
}

std::string Login::get_port() const
{
    return _inputs[InputType::PORT].getText();
}

std::string Login::get_username() const
{
    return _inputs[InputType::USERNAME].getText();
}


void Login::handleInput(void)
{
    if (_window.is_mouse_button(raylib::Window::PRESSED, 0) &&
        _window.get_mouse_position().x > 10 &&
        _window.get_mouse_position().x < 10 + 300 &&
        _window.get_mouse_position().y > 200 &&
        _window.get_mouse_position().y < 200 + 50) {
        _is_running = false;
    }
    if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_TAB) ||
        _window.is_key(raylib::Window::PRESSED, raylib::KEY_ENTER) ||
        _window.is_key(raylib::Window::PRESSED, raylib::KEY_DOWN)) {
        focus = (focus + 1) % 3;
    }
    char c = _window.get_char_pressed();
    if (c > 0 && _inputs[focus].getText().size() < 20) {
        _inputs[focus].setText(_inputs[focus].getText() + static_cast<char>(c));
    } else if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_BACKSPACE) && !_inputs[focus].getText().empty()) {
        _inputs[focus].setText(_inputs[focus].getText().substr(0, _inputs[focus].getText().size() - 1));
    }
}

bool Login::run()
{
    while (_is_running) {
        if (!_window.is_running()) {
            return true;
        }
        this->handleInput();
        _window.start_drawing();
        _window.draw_rectangle(150, 10 + focus * 50, 300, 40, raylib::GRAY);
        _window.draw_rectangle(8, 190, 350, 70, raylib::RED);
        for (auto &title : _titles) {
            title.draw();
        }
        for (auto &input : _inputs) {
            input.draw();
        }
        _window.end_drawing();
    }
    return false;
}
