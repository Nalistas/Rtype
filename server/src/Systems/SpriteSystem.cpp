/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SpriteSystem
*/

#include "Systems/SpriteSystem.hpp"

SpriteSystem::SpriteSystem(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{}

SpriteSystem::~SpriteSystem()
{}

void SpriteSystem::operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite)
{
    sprite.pos_x += static_cast<int>(sprite.speed_x) * _elpased_time;
    sprite.pos_y += static_cast<int>(sprite.speed_y) * _elpased_time;
}
