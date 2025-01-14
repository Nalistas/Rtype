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

    /**
     * @brief TextureManager. This class is here to ensure that the textures are loaded only once
     */
    class TextureManager {
        public:

            /**
             * @brief Get the Texture object
             * @param texture_path the path of the texture
             * @return std::shared_ptr<TextureCpp>
             */
            static std::shared_ptr<TextureCpp> getTexture(std::string const &texture_path);

        private:
            TextureManager();
            ~TextureManager();

            /**
             * @brief Get the instance object
             * @return TextureManager&
             */
            static TextureManager &getInstance();
            std::unordered_map<std::string, std::shared_ptr<TextureCpp>> _textures;
    };
}

#endif /* !TEXTUREMANAGER_HPP_ */
