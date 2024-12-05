/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemSprite
*/

#include "Systems/SystemSprite.hpp"

SystemSprite::SystemSprite()
{
}

SystemSprite::~SystemSprite()
{
}

void SystemSprite::operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), raylib::Sprite &sprite)
{
    sprite.draw();
}
