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
    this->_commandMap[1] = [this](std::vector<uint8_t> &data) {
        //define a background
        uint16_t backgroundId = data[1] * 256 + data[2]; 
        auto background = this->_backgrounds[backgroundId];
        background.auto_resize_x();
        background.auto_resize_y();
        this->_graphics.addBackground(background);
        std::cout << "Background " << backgroundId << " added" << std::endl;
    };

    this->_commandMap[2] = [this](std::vector<uint8_t> &data) {
        //create entity
        uint8_t entityType = data[1]; // 1 octet
        uint16_t entityId = data[2] * 256 + data[3];  // 2 octets
        uint32_t posX = data[4] * 16777216 + data[5] * 65536 + data[6] * 256 + data[7];      // 4 octets
        uint32_t posY = data[8] * 16777216 + data[9] * 65536 + data[10] * 256 + data[11];      // 4 octets
        uint8_t speedX = data[12];     // 1 octet
        uint8_t speedY = data[13];     // 1 octet

        auto sprite = this->_sprites.find(entityType);
        if (sprite == this->_sprites.end()) {
            std::cerr << "Sprite not found" << std::endl;
            return;
        }
        sprite->second.set_position(posX, posY);
        if (this->_entitiesSprites.find(entityId) != this->_entitiesSprites.end()) {
            this->_graphics.removeSprite(this->_entitiesSprites[entityId]);
        }
        this->_entitiesSprites[entityId] = this->_graphics.addSprite(sprite->second);
        this->_spritesSpeed[entityId] = {speedX, speedY};
        this->_graphics.onSpriteClick(6, [this, entityId]() {
            std::cout << "Entity " << entityId << " clicked" << std::endl;
        });
    };
    this->_commandMap[3] = [this](std::vector<uint8_t> &data) {
        uint16_t entityId = data[1] * 256 + data[2];
        if (this->_entitiesSprites.find(entityId) == this->_entitiesSprites.end()) {
            std::cerr << "Entity not found: " << entityId << std::endl;
            return;
        }
        this->_graphics.removeSprite(_entitiesSprites.at(entityId));
        _entitiesSprites.erase(entityId);
    };
    this->_commandMap[4] = [this](std::vector<uint8_t> &data) {
        //update speed
        uint16_t entityId = data[1] * 256 + data[2];
        uint8_t speedX = data[3];
        uint8_t speedY = data[4];

        auto entity = this->_entitiesSprites.find(entityId);
        if (entity == this->_entitiesSprites.end()) {
            std::cerr << "Entity not found" << std::endl;
            return;
        }
        this->_spritesSpeed[entityId] = {speedX, speedY};
    };
    this->_commandMap[5] = [this](std::vector<uint8_t> &data) {
        //update position
        uint16_t entityId = (data[1] << 8) + data[2]; // Combine les octets 1 et 2 pour obtenir un uint16_t

        uint32_t posX = (data[3] << 24) + (data[4] << 16) + (data[5] << 8) + data[6]; // Combine les octets 3 à 6 pour obtenir posX
        uint32_t posY = (data[7] << 24) + (data[8] << 16) + (data[9] << 8) + data[10]; // Combine les octets 7 à 10 pour obtenir posY

        auto entity = this->_entitiesSprites.find(entityId);
        if (entity == this->_entitiesSprites.end()) {
            std::cerr << "Entity not found" << std::endl;
            return;
        }
        auto &sprite = this->_graphics.getSprite(entity->second);
        sprite.set_position(posX, posY);
    };
    this->_commandMap[6] = [this](std::vector<uint8_t> &data) {
        //play music
        uint16_t musicId = data[1] * 256 + data[2];
        auto music = this->_musics.find(musicId);
        // this->_graphics.addMusic(music->second);
    };
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
        sprite.set_position(
            (sprite.get_position().x + (this->_spritesSpeed[entity.first].first * elapsed_time / 10)),
            (sprite.get_position().y + (this->_spritesSpeed[entity.first].second * elapsed_time / 10))
        );
    }
}

Game::~Game()
{
}
