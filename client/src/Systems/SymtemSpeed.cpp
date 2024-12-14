/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SymtemSpeed
*/

#include "SymtemSpeed.hpp"

SymtemSpeed::SymtemSpeed(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SymtemSpeed::~SymtemSpeed()
{
}


void SymtemSpeed::operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, Sprite &sprite)
{
    sprite->position.x += speed->getSpeed().x;
    sprite->position.y += speed->getSpeed().y;
}