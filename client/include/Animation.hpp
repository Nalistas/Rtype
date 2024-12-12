/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Animation
*/



#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

#include "Raylib/Sprite.hpp"

namespace raylib {
    #include "raylib.h"
}


class Animation {
    public:
        Animation();
        Animation(raylib::Sprite const &sprite);
        ~Animation();

    private:

        int _ms_per_frame;
        int _max_frame;
        int _current_frame;
        Rectangle _source_rect;
};

#endif /* !ANIMATION_HPP_ */
