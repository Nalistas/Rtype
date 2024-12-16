/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemDeleteEnemy
*/

#include "Systems/SystemDeleteEnemy.hpp"

SystemDeleteEnemy::SystemDeleteEnemy(std::function<void(ecs::entity const &)> broadcastDelete)
    : _broadcastDelete(broadcastDelete)
{
}

SystemDeleteEnemy::~SystemDeleteEnemy()
{
}

void SystemDeleteEnemy::operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite, Camp &camp)
{
    if (sprite.pos_x < 0 && camp.getCamp() == 1) {
        std::cout << sprite.pos_x << std::endl;
        std::cout << "delete enemy" << std::endl;
        _broadcastDelete(e);
        registry.delete_entity(e);
    }
}
