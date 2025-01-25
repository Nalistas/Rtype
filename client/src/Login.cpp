/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Login
*/

#include "Login.hpp"
#include "Background.hpp"
#include <array>

Login::Login() :
    focus(0),
    _window(620, 350),
    _is_running(true),
    _titles({
        raylib::RayText("Login", 250, 10, 50, raylib::WHITE),
        raylib::RayText("Name:", 10, 70, 30, raylib::WHITE),
        raylib::RayText("Ip:", 10, 120, 30, raylib::WHITE),
        raylib::RayText("Port:", 10, 170, 30, raylib::WHITE),
        raylib::RayText("Click to connect", 310, 300, 35, raylib::WHITE)
    }),
    _inputs({
        raylib::RayText("", 150, 70 + 50 * 0, 30, raylib::WHITE),
        raylib::RayText("", 150, 70 + 50 * 1, 30, raylib::WHITE),
        raylib::RayText("", 150, 70 + 50 * 2, 30, raylib::WHITE),
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
        _window.get_mouse_position().x > 310 &&
        _window.get_mouse_position().x < 310 + 300 &&
        _window.get_mouse_position().y > 300 &&
        _window.get_mouse_position().y < 300 + 50
        && !_inputs[InputType::USERNAME].getText().empty()) {
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
    Background background("../assets/space.png", _window.get_size().first, _window.get_size().second);
    background.setSpeed(0.5);
    background.setMoveType(Background::BACKGROUND_MOVE_TYPE::PARALLAX);
    background.loop(true);

    while (_is_running) {
        if (!_window.is_running()) {
            return true;
        }
        this->handleInput();
        background.draw();
        _window.start_drawing();
        _window.draw_rectangle(150, 70 + focus * 50, 300, 40, {211, 211, 211, 200});
        _window.draw_rectangle(300, 290, 350, 70, {153, 50, 204, 255});
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
