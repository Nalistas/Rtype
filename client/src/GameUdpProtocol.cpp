/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Game
*/

#include "Game.hpp"
#include "UdpClient.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;

void Game::processBackground(std::vector<uint8_t> &data)
{
    uint16_t backgroundId = data[1] * 256 + data[2]; 
    auto background = this->_backgrounds[backgroundId];
    background.auto_resize_x();
    background.auto_resize_y();
    this->_graphics.addBackground(background);
    std::cout << "Background " << backgroundId << " added" << std::endl;
}

void Game::processCreateEntity(std::vector<uint8_t> &data)
{
    uint8_t entityType = data[1];
    uint16_t entityId = data[2] * 256 + data[3];
    uint32_t pos_x = data[4] * 16777216 + data[5] * 65536 + data[6] * 256 + data[7];
    uint32_t pos_y = data[8] * 16777216 + data[9] * 65536 + data[10] * 256 + data[11];
    uint8_t speedX = data[12];
    uint8_t speedY = data[13];

    auto sprite = this->_sprites.find(entityType);
    if (sprite == this->_sprites.end()) {
        std::cerr << "Sprite not found" << std::endl;
        return;
    }
    std::cout << "Entity " << entityId << " added at " << pos_x << " " << pos_y << std::endl;
    sprite->second.set_position(pos_x, pos_y);
    if (this->_entitiesSprites.find(entityId) != this->_entitiesSprites.end()) {
        this->_graphics.removeSprite(this->_entitiesSprites[entityId]);
    }
    this->_entitiesSprites[entityId] = this->_graphics.addSprite(sprite->second);
    this->_spritesSpeed[entityId] = {speedX, speedY};
    this->_graphics.onSpriteClick(6, [this, entityId]() {
        std::cout << "Entity " << entityId << " clicked" << std::endl;
    });
}

void Game::processDeleteEntity(std::vector<uint8_t> &data)
{
    uint16_t entityId = data[1] * 256 + data[2];
    if (this->_entitiesSprites.find(entityId) == this->_entitiesSprites.end()) {
        std::cerr << "Entity not found: " << entityId << std::endl;
        this->_client.send({2});
        return;
    }
    this->_graphics.removeSprite(_entitiesSprites.at(entityId));
    _entitiesSprites.erase(entityId);
}

void Game::processUpdateSpeed(std::vector<uint8_t> &data)
{
    uint16_t entityId = data[1] * 256 + data[2];
    uint8_t speedX = data[3];
    uint8_t speedY = data[4];

    auto entity = this->_entitiesSprites.find(entityId);
    if (entity == this->_entitiesSprites.end()) {
        std::cerr << "Entity not found" << std::endl;
        this->_client.send({2});
        return;
    }
    this->_spritesSpeed[entityId] = {speedX, speedY};
}

void Game::processUpdatePosition(std::vector<uint8_t> &data)
{
    uint16_t entityId = (data[1] << 8) + data[2];

    uint32_t pos_x = (data[3] << 24) + (data[4] << 16) + (data[5] << 8) + data[6];
    uint32_t pos_y = (data[7] << 24) + (data[8] << 16) + (data[9] << 8) + data[10];

    auto entity = this->_entitiesSprites.find(entityId);
    if (entity == this->_entitiesSprites.end()) {
        std::cerr << "Entity not found" << std::endl;
        this->_client.send({2});
        return;
    }
    auto &sprite = this->_graphics.getSprite(entity->second);
    sprite.set_position(pos_x, pos_y);
}

void Game::playMusic(std::vector<uint8_t> &data)
{
    uint16_t musicId = data[1] * 256 + data[2];
    auto music = this->_musics.find(musicId);
}

void Game::processText(std::vector<uint8_t> &data)
{
    if (data.size() < 10) {
        std::cerr << "Not good :/" << std::endl; 
        return;
    }
    uint8_t id = data[1];
    uint8_t size = data[2];
    uint32_t pos_x = (data[3] << 24) + (data[4] << 16) + (data[5] << 8) + data[6];
    uint32_t pos_y = (data[7] << 24) + (data[8] << 16) + (data[9] << 8) + data[10];
    std::string value(data.begin() + 11, data.end());

    for (auto c : data) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << std::endl;


    std::cout << "GOOD !" << std::endl;

    std::cout << "ID: " << static_cast<int>(id) << std::endl;
    std::cout << "size: " << static_cast<int>(size) << std::endl;
    std::cout << "pos_x: " << pos_x << std::endl;
    std::cout << "pos_y: " << pos_y << std::endl;
    std::cout << "value: \"" << value << "\"" << std::endl;

    if (_entitiesText.find(id) == _entitiesText.end()) {
        std::cout << "adding text :)" << std::endl;
        raylib::RayText text(value, pos_x, pos_y, size, raylib::WHITE);
        _entitiesText[id] = _graphics.addText(text);
        return;
    }
    std::cout << "modifying text :)" << std::endl;
    auto &text = _graphics.getText(_entitiesText.at(id));
    text.setSize(size);
    text.setPosition(pos_x, pos_y);
    text.setText(value);
}
