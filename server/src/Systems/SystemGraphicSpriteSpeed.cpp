/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemGraphicSpriteSpeed
*/

#include "Systems/SystemGraphicSpriteSpeed.hpp"
#include <iostream>


SystemGraphicSpriteSpeed::SystemGraphicSpriteSpeed(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemGraphicSpriteSpeed::~SystemGraphicSpriteSpeed()
{
}

void SystemGraphicSpriteSpeed::operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite)
{

    (void)registry;
    (void)e;
    sprite.pos_x += sprite.speed_x * (static_cast<float>(this->_elpased_time) / 10.0f);
    sprite.pos_y += sprite.speed_y * (static_cast<float>(this->_elpased_time) / 10.0f);
    std::cout << "e: " << e << " : " << sprite.pos_x << " " << sprite.pos_y << std::endl;
}
