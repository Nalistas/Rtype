/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemSpeed
*/

#include "Systems/SystemSpeed.hpp"

SystemSpeed::SystemSpeed(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemSpeed::~SystemSpeed()
{
}

#include <iostream>

void SystemSpeed::operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, raylib::Sprite &sprite)
{
    raylib::Vector2 pos = sprite.get_position();

    pos.x += speed.getSpeed().x * (static_cast<float>(this->_elpased_time) / 10.0f);
    pos.y += speed.getSpeed().y * (static_cast<float>(this->_elpased_time) / 10.0f);
    sprite.set_position(pos.x, pos.y);
    std::cout << this->_elpased_time << " " << pos.x << " " << pos.y << std::endl;
}