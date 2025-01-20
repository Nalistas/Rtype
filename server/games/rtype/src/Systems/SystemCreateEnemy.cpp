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


SystemCreateEnemy::SystemCreateEnemy(rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players) :
    _creater(creater), _players(players)
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
    registry.get_components<Position>().emplace_at(enemy, Position{500, 200});
    registry.get_components<Hitbox>().emplace_at(enemy, Hitbox{25, 25});
    registry.get_components<Speed>().emplace_at(enemy, Speed{-1, 0});
    registry.get_components<Life>().emplace_at(enemy, Life{5});
    registry.get_components<SIDE>().emplace_at(enemy, SIDE::ENEMY);
    registry.get_components<Damage>().emplace_at(enemy, Damage{1});

    for (auto player : _players) {
        _creater(player.first, enemy, 1, 500, 200, -1, 0);
    }
    _ms_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
