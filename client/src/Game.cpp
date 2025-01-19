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
    for (auto &action : this->_actions[0]) {
        _graphics.addKeyBinding(action.first, false, [this, id = action.second]() {
            std::vector<uint8_t> udpMessage(13);
            udpMessage[0] = 1;
            *(uint32_t *)(udpMessage.data() + 1) = id;
            *(uint32_t *)(udpMessage.data() + 5) = static_cast<uint32_t>(this->_win.get_mouse_position().x);
            *(uint32_t *)(udpMessage.data() + 9) = static_cast<uint32_t>(this->_win.get_mouse_position().y);
            this->_client.send(udpMessage);
            for (auto c : udpMessage) {
                std::cout << static_cast<int>(c) << " ";
            }
        });
    }
}

void Game::interpretor(void)
{
    std::cout << "Interpretor" << std::endl;
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
    }
}

Game::~Game()
{
}
