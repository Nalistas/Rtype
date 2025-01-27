/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Game
*/

#include "Window.hpp"
#include "Game.hpp"
#include "UdpClient.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;

uint32_t Game::invert(uint32_t value)
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
    auto sendAction = [this](raylib::Vector2 pos, uint32_t id) {
        std::vector<uint8_t> udpMessage(13);
        udpMessage[0] = 1;
        *(uint32_t *)(udpMessage.data() + 1) = id;
        *(uint32_t *)(udpMessage.data() + 5) = invert(pos.x);
        *(uint32_t *)(udpMessage.data() + 9) = invert(pos.y);
        this->_client.send(udpMessage);
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
    this->_commandMap[1] = [this](std::vector<uint8_t> &data) { this->processBackground(data); };
    this->_commandMap[2] = [this](std::vector<uint8_t> &data) { this->processCreateEntity(data); };
    this->_commandMap[3] = [this](std::vector<uint8_t> &data) { this->processDeleteEntity(data); };
    this->_commandMap[4] = [this](std::vector<uint8_t> &data) { this->processUpdateSpeed(data); };
    this->_commandMap[5] = [this](std::vector<uint8_t> &data) { this->processUpdatePosition(data); };
    this->_commandMap[6] = [this](std::vector<uint8_t> &data) { this->playMusic(data); };
    this->_commandMap[7] = [this](std::vector<uint8_t> &data) { this->processText(data); };
}


void Game::interpretor(void)
{
    while (this->_client.hasData()) {
        auto udpResponse = this->_client.receive();
        if (_commandMap.find(udpResponse[0]) != _commandMap.end()) {
            _commandMap[udpResponse[0]](udpResponse);
        } else {
            std::cout << "Command not found : " ;
            for (auto c : udpResponse) {
                std::cout << static_cast<int>(c) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Game::run(void)
{
    _ms_last_update = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    this->_client.send({2});
    while (this->_win.is_running()) {
        this->interpretor();
        this->moveSprites();
        this->_graphics.display();
    }
}

void Game::moveSprites(void)
{
    auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto elapsed_time = now - _ms_last_update;
    if (elapsed_time < 10) {
        std::cout << "GameCore: " << elapsed_time << " stopping" << std::endl;
        return;
    }
    _ms_last_update = now;
    for (auto &entity : _entitiesSprites) {
        auto &sprite = _graphics.getSprite(entity.second);
        float posX = sprite.get_position().x + (this->_spritesSpeed[entity.first].first * elapsed_time / 10);
        float posY = sprite.get_position().y + (this->_spritesSpeed[entity.first].second * elapsed_time / 10);
        sprite.set_position(posX, posY);
    }
}

Game::~Game()
{
}
