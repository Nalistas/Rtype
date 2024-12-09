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
        /**
         * @brief Construct a new System Sprite object
         */
        SystemSprite();

        /**
         * @brief Destroy the System Sprite object
         */
        ~SystemSprite();

        /**
         * @brief Call the system
         */
        void operator()(ecs::registry &registry, ecs::entity const &e, raylib::Sprite &sprite) override;

};

#endif /* !SYSTEMSPRITE_HPP_ */
