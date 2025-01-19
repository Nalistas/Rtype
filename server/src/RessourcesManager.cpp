/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** RessourcesManager
*/

#include "RessourcesManager.hpp"

RessourcesManager::RessourcesManager(std::unique_ptr<rtype::IGame> &game)
{
    uint32_t i = 0;

    for (auto &background : game->getBackgrounds()) {
        _ressources.push_back(transformBackground(background, i));
        i++;
    }
    i = 0;
    for (auto &sprite : game->getSprites()) {
        _ressources.push_back(transformSprite(sprite, i));
        i++;
    }
    i = 0;
    for (auto &music : game->getMusics()) {
        _ressources.push_back(transformMusic(music, i));
        i++;
    }
    i = 0;
    for (auto &action : game->getClientActionHandlers()) {
        _ressources.push_back(transformAction(action, i));
        i++;
    }
    _game_name = game->getName();
}

RessourcesManager::~RessourcesManager()
{}

std::list<std::vector<uint8_t>> &RessourcesManager::getRessourcess()
{
    return _ressources;
}

void RessourcesManager::copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value)
{
    vec[pos + 3] = value & 0xFF;
    vec[pos + 2] = (value / 256) & 0xFF;
    vec[pos + 1] = (value / 65536) & 0xFF;
    vec[pos] = (value / 16777216) & 0xFF;
}

std::vector<uint8_t> RessourcesManager::transformBackground(rtype::Background const &background, uint32_t id)
{
    std::vector<uint8_t> buffer(10 + background.path.length());

    buffer[0] = 4;
    this->copyUint32(buffer, 1, id);
    buffer[5] = background.speed;
    buffer[6] = background.direction;
    buffer[7] = background.loop;
    buffer[8] = background.resize;
    buffer[9] = background.type;
    std::copy(background.path.begin(), background.path.end(), buffer.begin() + 10);
    return buffer;
}

std::vector<uint8_t> RessourcesManager::transformSprite(rtype::Sprite const &sprite, uint32_t id)
{
    std::vector<uint8_t> buffer(34 + sprite.path.length());

    buffer[0] = 3;
    this->copyUint32(buffer, 1, id);
    this->copyUint32(buffer, 5, sprite.size_x);
    this->copyUint32(buffer, 9, sprite.size_y);
    this->copyUint32(buffer, 13, sprite.texture_rect_size_x);
    this->copyUint32(buffer, 17, sprite.texture_rect_size_y);
    this->copyUint32(buffer, 21, sprite.texture_rect_offset_x);
    this->copyUint32(buffer, 25, sprite.texture_rect_offset_y);
    buffer[29] = sprite.nb_frames;
    this->copyUint32(buffer, 30, sprite.ms_per_frame);
    std::copy(sprite.path.begin(), sprite.path.end(), buffer.begin() + 34);
    return buffer;
}

std::vector<uint8_t> RessourcesManager::transformMusic(std::string const &music, uint32_t id)
{
    std::vector<uint8_t> buffer(5 + music.length());

    buffer[0] = 5;
    this->copyUint32(buffer, 1, id);
    std::copy(music.begin(), music.end(), buffer.begin() + 5);
    return buffer;
}

std::vector<uint8_t> RessourcesManager::transformAction(rtype::ClientAction const &action, uint32_t id)
{
    std::vector<uint8_t> buffer(10);

    buffer[0] = 6;
    this->copyUint32(buffer, 1, id);
    this->copyUint32(buffer, 5, action.key);
    buffer[9] = action.pressed ? 1 : 0;
    return buffer;
}

std::string const &RessourcesManager::getGameName() const
{
    return _game_name;
}
