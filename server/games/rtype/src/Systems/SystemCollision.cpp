/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "Systems/SystemCollision.hpp"

SystemCollision::SystemCollision(rtype::IGame::Deleter creater)
    : _deleter(creater)
{
}

SystemCollision::~SystemCollision()
{
}

void SystemCollision::operator()(ecs::registry &registry, Position &position, Hitbox &hitbox, Damage &damage)
{
    
}
