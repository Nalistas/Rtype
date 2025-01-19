/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Game
*/

#include "Game.hpp"
#include "UdpClient.hpp"
#include "Window.hpp"
#include <iostream>

uint32_t invert(uint32_t value)
{
    return ((value & 0x000000FF) << 24) | // Byte 0 -> Byte 3
           ((value & 0x0000FF00) << 8)  | // Byte 1 -> Byte 2
           ((value & 0x00FF0000) >> 8)  | // Byte 2 -> Byte 1
           ((value & 0xFF000000) >> 24);  // Byte 3 -> Byte 0
}

Game::Game(
    std::array<std::map<uint32_t, uint32_t>, 2> actions,
    std::map<uint32_t, raylib::Sprite> &sprites,
    std::map<uint32_t, Background> &backgrounds,
    std::map<uint32_t, raylib::RayMusic> &musics,
    UdpClient &client,
    raylib::Window &win
) :
    _actions(actions), _sprites(sprites), _backgrounds(backgrounds), _musics(musics), _client(client), _win(win), _graphics(win)
{
    std::cout << "Game constructor" << std::endl;

    auto sendAction = [this](raylib::Vector2 pos, uint32_t id) {
        std::vector<uint8_t> udpMessage(13);
        udpMessage[0] = 1;
        *(uint32_t *)(udpMessage.data() + 1) = id;
        *(uint32_t *)(udpMessage.data() + 5) = invert(pos.x);
        *(uint32_t *)(udpMessage.data() + 9) = invert(pos.y);
        this->_client.send(udpMessage);
        for (auto c : udpMessage) {
            std::cout << static_cast<int>(c) << " ";
        }
    };

    for (auto &action : this->_actions[0]) {
        _graphics.addKeyBinding(invert(action.first), false, [this, id = action.second, sendAction]() {
            sendAction(this->_win.get_mouse_position(), id);
        });
    }
    for (auto &action : this->_actions[1]) {
        _graphics.addKeyBinding(invert(action.first), true, [this, id = action.second, sendAction]() {
            sendAction(this->_win.get_mouse_position(), id);
        });
    }
}

void Game::interpretor(void)
{
    if (this->_client.hasData()) {
        auto udpResponse = this->_client.receive();
        for (auto c : udpResponse) {
            std::cout << static_cast<int>(c) << " ";
        }
        std::cout << std::endl;
    }
}

void Game::run(void)
{
    std::cout << "RUNNING !!!" << std::endl;
    while (this->_win.is_running()) {
        this->interpretor();
        this->_graphics.display();
    }
}

Game::~Game()
{
}
