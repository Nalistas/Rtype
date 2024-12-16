/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GraphicsPrimitives
*/

#include "GraphicsPrimitives.hpp"
#include <cstring>


std::vector<char> graphics_interface::Background::encode(void)
{
    std::vector<char> data;
    std::size_t short_size = sizeof(Background) - sizeof(std::string);

    data.resize(short_size + this->path.size());
    std::memcpy(data.data(), this, short_size);
    for (std::size_t i = 0; i < this->path.size(); i++) {
        data[short_size + i] = this->path[i];
    }
    return data;
}

void graphics_interface::Background::decode(std::vector<char> const &data)
{
    std::size_t short_size = sizeof(Background) - sizeof(std::string);

    this->path.resize(data.size() - short_size);
    std::memcpy((void *)this, data.data(), short_size);
    for (std::size_t i = 0; i < this->path.size(); i++) {
        this->path[i] = data[short_size + i];
    }
}

std::vector<char> graphics_interface::Sprite::encode(void)
{
    std::vector<char> data;
    std::size_t short_size = sizeof(Sprite) - sizeof(std::string);

    data.resize(short_size + this->path.size());
    std::memcpy(data.data(), this, short_size);
    for (std::size_t i = 0; i < this->path.size(); i++) {
        data[short_size + i] = this->path[i];
    }
    return data;
}

void graphics_interface::Sprite::decode(std::vector<char> const &data)
{
    Sprite sprite;
    std::size_t short_size = sizeof(Sprite) - sizeof(std::string);

    sprite.path.resize(data.size() - short_size);
    std::memcpy((void *)&sprite, data.data(), short_size);
    for (std::size_t i = 0; i < sprite.path.size(); i++) {
        sprite.path[i] = data[short_size + i];
    }
    *this = sprite;
}

void graphics_interface::Sound::decode(std::vector<char> const &data)
{
    std::string path;
    path.resize(data.size());
    for (std::size_t i = 0; i < data.size(); i++) {
        path[i] = data[i];
    }
    this->path = path;
}

std::vector<char> graphics_interface::Sound::encode(void)
{
    std::vector<char> data;
    data.resize(this->path.size());
    for (std::size_t i = 0; i < this->path.size(); i++) {
        data[i] = this->path[i];
    }
    return data;
}

void graphics_interface::Music::decode(std::vector<char> const &data)
{
    std::string path;
    path.resize(data.size());
    for (std::size_t i = 0; i < data.size(); i++) {
        path[i] = data[i];
    }
    this->path = path;
}

std::vector<char> graphics_interface::Music::encode(void)
{
    std::vector<char> data;
    data.resize(this->path.size());
    for (std::size_t i = 0; i < this->path.size(); i++) {
        data[i] = this->path[i];
    }
    return data;
}
