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
    this->_commandMap[1] = [this](std::vector<uint8_t> &data) {
        //define a background
        std::cout << "COUCOU HERE" << std::endl;
        uint16_t backgroundId = data[1] * 256 + data[2]; 
        std::cout << "Background id: " << backgroundId << std::endl;
        auto background = this->_backgrounds[backgroundId];
        this->_graphics.addBackground(background);
    };

    this->_commandMap[2] = [this](std::vector<uint8_t> &data) {
        //create entity
        uint8_t entityType = data[1]; // 1 octet
        uint16_t entityId = data[2] * 256 + data[3];  // 2 octets
        uint32_t posX = data[4] * 16777216 + data[5] * 65536 + data[6] * 256 + data[7];      // 4 octets
        uint32_t posY = data[8] * 16777216 + data[9] * 65536 + data[10] * 256 + data[11];      // 4 octets
        uint8_t speedX = data[12];     // 1 octet
        uint8_t speedY = data[13];     // 1 octet

        auto sprite = this->_sprites[entityType];
        auto entity = this->_entitiesSprites[entityId];

        sprite.set_position(posX, posY);
        if (entity == 0) { // à quoi sert le if ici ? ????
            this->_entitiesSprites[entityId] = this->_graphics.addSprite(sprite);
        }
    };
    this->_commandMap[3] = [this](std::vector<uint8_t> &data) {
        uint16_t entityId = data[1] * 256 + data[2];
        this->_graphics.removeSprite(_entitiesSprites.at(entityId));
        _entitiesSprites.erase(entityId);
    };
    this->_commandMap[4] = [this](std::vector<uint8_t> &data) {
        //update speed
        uint16_t entityId = data[1] * 256 + data[0];
        uint8_t speedX = data[4];
        uint8_t speedY = data[5];

        // faut faire quelque part la logique de vitesse
        auto entity = this->_entitiesSprites[entityId];
        if (entity != 0) {
            auto sprite = this->_graphics.getSprite(entity);
        }
    };
    this->_commandMap[5] = [this](std::vector<uint8_t> &data) {
        //update position
        uint16_t entityId = data[1] * 256 + data[2];
        uint32_t posX = data[3] * 16777216 + data[6] * 65536 + data[7] * 256 + data[8];
        uint32_t posY = data[7] * 16777216 + data[8] * 65536 + data[9] * 256 + data[10];

        auto entity = this->_entitiesSprites.find(entityId);
        if (entity != this->_entitiesSprites.end()) {
            auto sprite = this->_graphics.getSprite(entity->second);
            sprite.set_position(posX, posY);
        }
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
    if (this->_client.hasData()) {
        auto udpResponse = this->_client.receive();
        for (auto c : udpResponse) {
            std::cout << static_cast<int>(c) << " ";
        }
        if (_commandMap.find(udpResponse[0]) != _commandMap.end()) {
            std::cout << "Command found\n";
            _commandMap[udpResponse[0]](udpResponse);
        }
        std::cout << std::endl;
    }
}

void Game::run(void)
{
    this->_client.send({2});
    while (this->_win.is_running()) {
        this->interpretor();
        this->moveSprites();
        this->_graphics.display();
    }
}

void Game::moveSprites(void)
{
    for (auto &entity : _entitiesSprites) {
        auto sprite = _graphics.getSprite(entity.second);
        sprite.set_position(sprite.get_position().x + 1, sprite.get_position().y);
    }
}

Game::~Game()
{
}
