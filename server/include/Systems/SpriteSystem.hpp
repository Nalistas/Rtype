/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SpriteSystem
*/

#include "isystem.hpp"
#include "GraphicsPrimitives.hpp"

#ifndef SPRITESYSTEM_HPP_
    #define SPRITESYSTEM_HPP_

class SpriteSystem : public ecs::isystem<graphics_interface::Sprite> {
    public:
        SpriteSystem(std::size_t const &elpased_time);
        ~SpriteSystem();

        void operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite) override;
    private:
        std::size_t const &_elpased_time;
};

#endif /* !SPRITESYSTEM_HPP_ */
