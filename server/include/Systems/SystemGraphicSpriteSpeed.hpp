/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemGraphicSpriteSpeed
*/

#include "GraphicsPrimitives.hpp"
#include "isystem.hpp"
// #include "Speed.hpp"

#ifndef SYSTEMGRAPHICSPRITESPEED_HPP_
#define SYSTEMGRAPHICSPRITESPEED_HPP_

class SystemGraphicSpriteSpeed: public ecs::isystem<graphics_interface::Sprite> {
    public:
        /**
         * @brief Construct a new System Speed object
         * @param elpased_time the reference to the elpased time
         */
        SystemGraphicSpriteSpeed(std::size_t const &elpased_time);
        ~SystemGraphicSpriteSpeed();
        void operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite);

    protected:
    private:
            std::size_t const &_elpased_time;

};

#endif /* !SYSTEMGRAPHICSPRITESPEED_HPP_ */
