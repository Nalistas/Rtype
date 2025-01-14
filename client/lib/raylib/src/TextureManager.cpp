/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TextureManager
*/

#include <stdexcept>
#include "TextureManager.hpp"

raylib::TextureManager::TextureManager()
{
}

raylib::TextureManager::~TextureManager()
{
}

std::shared_ptr<raylib::TextureCpp> raylib::TextureManager::getTexture(std::string const &texture_path)
{
    if (getInstance()._textures.find(texture_path) == getInstance()._textures.end()) {
        getInstance()._textures[texture_path] = std::make_shared<raylib::TextureCpp>(texture_path);
        if (!getInstance()._textures[texture_path]) {
            throw std::runtime_error("Failed to load texture: " + texture_path);
        }
    }
    return getInstance()._textures[texture_path];
}

raylib::TextureManager &raylib::TextureManager::getInstance()
{
    static raylib::TextureManager instance;
    return instance;
}
