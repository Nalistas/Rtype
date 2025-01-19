/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemBroadcast
*/

#include "Systems/SystemBroadcast.hpp"
#include "zipper.hpp"
#include "registry.hpp"

SystemBroadcast::SystemBroadcast(rtype::IGame::SpeedUpdater &speedUpdater, rtype::IGame::PositionUpdater &positionUpdater, std::unordered_map<std::size_t, std::size_t> &players)
    : _speedUpdater(speedUpdater), _positionUpdater(positionUpdater), _players(players)
{
}

SystemBroadcast::~SystemBroadcast()
{
}

void SystemBroadcast::operator()(ecs::registry &registry, sparse_array<Speed> &speed, sparse_array<Position> &pos)
{
    auto speeds = registry.get_components<Speed>();
    auto positions = registry.get_components<Position>();

    for (auto [index, speed, position] : zipper(speeds, positions)) {
        if (speed.has_value()) {
            for (auto player : _players) {
                _speedUpdater(player.first, index, speed.value().x, speed.value().y);
            }
        }
        if (position.has_value()) {
            for (auto player: _players) {
                _positionUpdater(player.second, index, position.value().x, position.value().y);
            }
        }
    }
}
