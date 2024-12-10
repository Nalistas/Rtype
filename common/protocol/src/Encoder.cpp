/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** graphics
*/

#include "Encoder.hpp"
#include <cstring>

std::vector<char> rtype_protocol::Encoder::encode(Background const &background)
{
    std::vector<char> data;
    std::size_t short_size = sizeof(Background) - sizeof(std::string);

    data.resize(short_size + background.path.size());
    std::memcpy(data.data(), &background, short_size);
    for (std::size_t i = 0; i < background.path.size(); i++) {
        data[short_size + i] = background.path[i];
    }
    return data;
}

std::vector<char> rtype_protocol::Encoder::encode(Sprite const &sprite)
{
    std::vector<char> data;
    std::size_t short_size = sizeof(Sprite) - sizeof(std::string);

    data.resize(short_size + sprite.path.size());
    std::memcpy(data.data(), &sprite, short_size);
    for (std::size_t i = 0; i < sprite.path.size(); i++) {
        data[short_size + i] = sprite.path[i];
    }
    return data;
}

std::vector<char> rtype_protocol::Encoder::encode(Music const &music)
{
    std::vector<char> data;

    data.resize(music.path.size());
    for (std::size_t i = 0; i < music.path.size(); i++) {
        data[i] = music.path[i];
    }
    return data;
}

std::vector<char> rtype_protocol::Encoder::encode(Sound const &sound)
{
    std::vector<char> data;

    data.resize(sound.path.size());
    for (std::size_t i = 0; i < sound.path.size(); i++) {
        data[i] = sound.path[i];
    }
    return data;
}

rtype_protocol::Background rtype_protocol::Encoder::decodeBackground(std::vector<char> const &data)
{
    Background background;
    std::size_t short_size = sizeof(Background) - sizeof(std::string);

    std::memcpy((void *)&background, data.data(), short_size);
    background.path.resize(data.size() - short_size);
    for (std::size_t i = 0; i < background.path.size(); i++) {
        background.path[i] = data[short_size + i];
    }
    return background;
}

rtype_protocol::Sprite rtype_protocol::Encoder::decodeSprite(std::vector<char> const &data)
{
    Sprite sprite;
    std::size_t short_size = sizeof(Sprite) - sizeof(std::string);

    std::memcpy((void *)&sprite, data.data(), short_size);
    sprite.path.resize(data.size() - short_size);
    for (std::size_t i = 0; i < sprite.path.size(); i++) {
        sprite.path[i] = data[short_size + i];
    }
    return sprite;
}

rtype_protocol::Music rtype_protocol::Encoder::decodeMusic(std::vector<char> const &data)
{
    Music music;
    music.path.resize(data.size());
    for (std::size_t i = 0; i < music.path.size(); i++) {
        music.path[i] = data[i];
    }
    return music;
}

rtype_protocol::Sound rtype_protocol::Encoder::decodeSound(std::vector<char> const &data)
{
    Sound sound;
    sound.path.resize(data.size());
    for (std::size_t i = 0; i < sound.path.size(); i++) {
        sound.path[i] = data[i];
    }
    return sound;
}
