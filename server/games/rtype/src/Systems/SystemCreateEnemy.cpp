/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCreateEnemy
*/

#include "Systems/SystemCreateEnemy.hpp"
#include <chrono>
#include "zipper.hpp"
#include "registry.hpp"
// #include "components.hpp"


SystemCreateEnemy::SystemCreateEnemy(rtype::IGame::Creater creater) : _creater(creater)
{
    _ms_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

SystemCreateEnemy::~SystemCreateEnemy()
{
}

void SystemCreateEnemy::operator()(ecs::registry &registry)
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() - _ms_last_update < 1000) {
        return;
    }
    auto enemy = registry.create_entity();
    registry.get_components<Position>().insert_at(enemy, Position{0, 0});
    registry.get_components<Hitbox>().insert_at(enemy, Hitbox{20, 20});
    registry.get_components<Speed>().insert_at(enemy, Speed{0, 0});
    registry.get_components<Life>().insert_at(enemy, Life{5});
    registry.get_components<SIDE>().insert_at(enemy, SIDE::ENEMY);
    registry.get_components<Damage>().insert_at(enemy, Damage{1});

    // broadcast to all players
}
