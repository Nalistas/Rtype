/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SymtemSpeed
*/

#include "SymtemSpeed.hpp"

SymtemSpeed::SymtemSpeed()
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