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
        void setFrame(int frame);
        void setMaxFrame(int max_frame);
        void setMsPerFrame(int ms_per_frame);
        void setSourceRect(raylib::Rectangle const &source_rect);
        raylib::Rectangle getSourceRect() const;
        int getFrame() const;
        int getMaxFrame() const;
        int getMsPerFrame() const;

    private:

        int _ms_per_frame;
        int _max_frame;
        int _current_frame;
        raylib::Rectangle _source_rect;
};

#endif /* !ANIMATION_HPP_ */
