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
            TextureCpp(std::string const &texture_path) { _texture = LoadTexture(texture_path.c_str()); };
            ~TextureCpp() { UnloadTexture(_texture); };

            Texture2D get_texture() const { return _texture; }

        private:
            Texture2D _texture;
    };
} // namespace raylib


#endif /* !TEXTURE_HPP_ */
