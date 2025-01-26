/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemShootEnemyBullet
*/

#include "Systems/SystemShootEnemyBullet.hpp"
#include <chrono>
#include "zipper.hpp"
#include "registry.hpp"

SystemShootEnemyBullet::SystemShootEnemyBullet(rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players) :
    _creater(creater), _players(players)
{
    _ms_last_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

SystemShootEnemyBullet::~SystemShootEnemyBullet()
{
}

void SystemShootEnemyBullet::operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Type> &types, sparse_array<SIDE> &sides)
{
    // if (std::chrono::duration_cast<std::chrono::milliseconds>(
    //     std::chrono::system_clock::now().time_since_epoch()
    // ).count() - _ms_last_update < 2000) {
    //     return;
    // }

    // for (auto [index, position, type, side] : zipper(positions, types, sides)) {
        // if (side.value() != SIDE::ENEMY && type.value() != Type::SHOOTER) continue;

        // auto bullet = registry.create_entity();
        // registry.get_components<Position>().emplace_at(bullet, Position{position->x - 35, position->y});
        // registry.get_components<Speed>().emplace_at(bullet, Speed{-2, 0});
        // registry.get_components<Hitbox>().emplace_at(bullet, Hitbox{1, 1});
        // registry.get_components<Damage>().emplace_at(bullet, Damage{1});
        // registry.get_components<SIDE>().emplace_at(bullet, SIDE::ENEMY);

        // for (auto player : _players) {
        //     _creater(player.first, bullet, 4,
        //         registry.get_components<Position>()[bullet].value().x,
        //         registry.get_components<Position>()[bullet].value().y,
        //         registry.get_components<Speed>()[bullet].value().x,
        //         registry.get_components<Speed>()[bullet].value().y);
        // }

    // }
}
