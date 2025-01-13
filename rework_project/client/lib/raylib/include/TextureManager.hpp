/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TextureManager
*/

#include <string>
#include <unordered_map>
#include <memory>

#ifndef TEXTUREMANAGER_HPP_
    #define TEXTUREMANAGER_HPP_

#include "Texture.hpp"

namespace raylib {
    #include "raylib.h"

    class TextureManager {
        public:

            static std::shared_ptr<TextureCpp> getTexture(std::string const &texture_path);

        private:
            TextureManager();
            ~TextureManager();

            static TextureManager &getInstance();
            std::unordered_map<std::string, std::shared_ptr<TextureCpp>> _textures;
    };
}

#endif /* !TEXTUREMANAGER_HPP_ */
