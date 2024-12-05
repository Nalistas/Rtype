/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemSprite
*/

#include "isystem.hpp"
#include "Raylib/Sprite.hpp"

#ifndef SYSTEMSPRITE_HPP_
    #define SYSTEMSPRITE_HPP_

class SystemSprite : public ecs::isystem<raylib::Sprite> {
    public:
        SystemSprite();
        ~SystemSprite();

        void operator()(ecs::iregistry &registry, ecs::entity const &e, raylib::Sprite &sprite) override;

};

#endif /* !SYSTEMSPRITE_HPP_ */
