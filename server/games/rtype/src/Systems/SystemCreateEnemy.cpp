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

    _nb_enemies = 0;
}

SystemCreateEnemy::~SystemCreateEnemy()
{
}

void SystemCreateEnemy::operator()(ecs::registry &registry)
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() - _ms_last_update < 2000) {
        return;
    }

    if (_nb_enemies % 3 == 0) {
        createEnemy2(registry);
    } else {
        createEnemy1(registry);
    }
    _nb_enemies++;
}

void SystemCreateEnemy::createEnemy1(ecs::registry &registry)
{
    auto enemy = registry.create_entity();
    registry.get_components<Position>().emplace_at(enemy, Position{950, static_cast<int>(random()) % 500});
    registry.get_components<Hitbox>().emplace_at(enemy, Hitbox{50, 50});
    registry.get_components<Speed>().emplace_at(enemy, Speed{-1, 0});
    registry.get_components<Life>().emplace_at(enemy, Life{1});
    registry.get_components<SIDE>().emplace_at(enemy, SIDE::ENEMY);
    registry.get_components<Damage>().emplace_at(enemy, Damage{1});
    registry.get_components<Type>().emplace_at(enemy, Type::BASIC);

    for (auto player : _players) {
        _creater(player.first, enemy, 1, 500, 200, -1, 0);
    }
    _ms_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void SystemCreateEnemy::createEnemy2(ecs::registry &registry)
{
    auto enemy = registry.create_entity();
    registry.get_components<Position>().emplace_at(enemy, Position{950, static_cast<int>(random()) % 500});
    registry.get_components<Hitbox>().emplace_at(enemy, Hitbox{50, 50});
    registry.get_components<Speed>().emplace_at(enemy, Speed{-1, 0});
    registry.get_components<Life>().emplace_at(enemy, Life{3});
    registry.get_components<SIDE>().emplace_at(enemy, SIDE::ENEMY);
    registry.get_components<Damage>().emplace_at(enemy, Damage{1});
    registry.get_components<Type>().emplace_at(enemy, Type::SHOOTER);

    for (auto player : _players) {
        _creater(player.first, enemy, 3, 500, 200, -1, 0);
    }
    _ms_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
