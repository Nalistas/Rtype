/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** RtypePlayer
*/

#include <utility>
#include <cstddef>
#include "GraphicsPrimitives.hpp"

#ifndef RTYPEPLAYER_HPP_
    #define RTYPEPLAYER_HPP_

class RtypePlayer {
    public:
        RtypePlayer();
        ~RtypePlayer();

        const std::pair<std::size_t, std::size_t> &getPosition(void) const;

        void setPosition(std::size_t x, std::size_t y);


        const std::pair<std::size_t, std::size_t> &getSpeed(void) const;

        void setSpeed(std::size_t x, std::size_t y);

        void setHealth(std::size_t health);

        size_t getHealth(void) const;

        graphics_interface::Sprite &getSprite();
        void setSpritePath(std::string path);

    private:
        std::pair<std::size_t, std::size_t> _position;
        std::pair<std::size_t, std::size_t> _speed;
        size_t _health;
        graphics_interface::Sprite _sprite;

};

#endif /* !RTYPEPLAYER_HPP_ */
