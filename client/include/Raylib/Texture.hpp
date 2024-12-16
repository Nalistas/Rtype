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


    class TextureCpp {
        public:
            TextureCpp(std::string const &texture_path) { _texture = LoadTexture(texture_path.c_str()); _texture_path = texture_path; };
            ~TextureCpp() { UnloadTexture(_texture); };

            Texture2D get_texture() const { return _texture; }
            std::string get_texture_path() const { return _texture_path; }

        private:
            Texture2D _texture;
            std::string _texture_path;
    };
} // namespace raylib


#endif /* !TEXTURE_HPP_ */
