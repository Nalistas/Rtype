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
    this->_commandMap[1] = [this](std::istringstream &iss) {
        //define a background
        uint8_t backgroundId;
        int tempBackgroundId;
        iss >> tempBackgroundId;
        backgroundId = static_cast<uint8_t>(tempBackgroundId);
        auto background = this->_backgrounds[backgroundId];
        this->_graphics.addBackground(background);
    };

    this->_commandMap[2] = [this](std::istringstream &iss) {
        //create entity
        uint8_t entityType; // 1 octet
        uint16_t entityId;  // 2 octets
        uint32_t posX;      // 4 octets
        uint32_t posY;      // 4 octets
        uint8_t speedX;     // 1 octet
        uint8_t speedY;     // 1 octet

        int tempEntityType, tempSpeedX, tempSpeedY;
        iss >> tempEntityType >> entityId >> posX >> posY >> tempSpeedX >> tempSpeedY;

        entityType = static_cast<uint8_t>(tempEntityType);
        speedX = static_cast<uint8_t>(tempSpeedX);
        speedY = static_cast<uint8_t>(tempSpeedY);

        auto sprite = this->_sprites[entityType];
        auto entity = this->_entitiesSprites[entityId];
        if (entity == 0) {
            this->_entitiesSprites[entityId] = this->_graphics.addSprite(sprite);

        }
    };
    this->_commandMap[3] = [this](std::istringstream &iss) {
        //delete entity
        uint16_t entityId;
        iss >> entityId;
        _entitiesSprites.erase(entityId);
    };
    this->_commandMap[4] = [this](std::istringstream &iss) {
        //update speed
        uint16_t entityId;
        uint8_t speedX;
        uint8_t speedY;
        iss >> entityId >> speedX >> speedY;
        auto entity = this->_entitiesSprites[entityId];
        if (entity != 0) {
            auto sprite = this->_graphics.getSprite(entity);
        }
    };
    this->_commandMap[5] = [this](std::istringstream &iss) {
        //update position
        uint16_t entityId;
        uint32_t posX;
        uint32_t posY;
        iss >> entityId >> posX >> posY;
        auto entity = this->_entitiesSprites[entityId];
        if (entity != 0) {
            auto sprite = this->_graphics.getSprite(entity);
            sprite.set_position(posX, posY);
        }
    };
    this->_commandMap[6] = [this](std::istringstream &iss) {
        //play music
        uint8_t musicId;
        iss >> musicId;
        auto music = this->_musics[musicId];
        music.play();
    };
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
    this->_client.send({2});
    while (this->_win.is_running()) {
        this->interpretor();
        this->_graphics.display();
    }
}

Game::~Game()
{
}
