/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Texture
*/

#include <string>

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

namespace raylib {
    #include "raylib.h"

    /**
     * @brief Texture class to handle the textures with raylib
     */
    class TextureCpp {
        public:
            /**
             * @brief Construct a new Texture object
             * 
             * @param texture_path the path to the texture
             */
            TextureCpp(std::string const &texture_path) { _texture = LoadTexture(texture_path.c_str()); _texture_path = texture_path; };
            ~TextureCpp() { UnloadTexture(_texture); };

            /**
             * @brief Get the texture
             * @return the texture
             */
            Texture2D get_texture() const { return _texture; }

            /**
             * @brief Get the texture path
             * @return the texture path
             */
            std::string get_texture_path() const { return _texture_path; }

        private:
            Texture2D _texture;
            std::string _texture_path;
    };
} // namespace raylib


#endif /* !TEXTURE_HPP_ */
