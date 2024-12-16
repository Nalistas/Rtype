/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemManageBullets
*/

#include "Systems/SystemManageBullets.hpp"
#include "Health.hpp"
#include "Camp.hpp"
#include "Systems/SystemComputeSingleBullet.hpp"

SystemManageBullets::SystemManageBullets(std::function<void(ecs::entity const &)> broadcastDelete)
        : _broadcastDelete(broadcastDelete)
{
}

SystemManageBullets::~SystemManageBullets()
{
}

void SystemManageBullets::operator()(ecs::registry &r , ecs::entity const &e, graphics_interface::Sprite &sprite, Camp &camp, Damage &damage)
{
    r.run_single_system<Health, graphics_interface::Sprite, Camp>(SystemComputeSingleBullet(camp, damage, sprite, _broadcastDelete));
}
