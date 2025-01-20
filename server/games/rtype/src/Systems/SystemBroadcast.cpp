/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemBroadcast
*/

#include "Systems/SystemBroadcast.hpp"
#include "zipper.hpp"
#include "registry.hpp"
#include <chrono>

using namespace std::chrono;

SystemBroadcast::SystemBroadcast(rtype::IGame::SpeedUpdater &speedUpdater, rtype::IGame::PositionUpdater &positionUpdater, std::unordered_map<std::size_t, std::size_t> &players)
    : _speedUpdater(speedUpdater), _positionUpdater(positionUpdater), _players(players)
{
    _ms_last_update = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

SystemBroadcast::~SystemBroadcast()
{
}

void SystemBroadcast::operator()(ecs::registry &registry, sparse_array<Speed> &speeds, sparse_array<Position> &pos)
{
    auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto time_elapsed = time - _ms_last_update;
    if (time_elapsed < 500) {
        return;
    }
    _ms_last_update = time;

    for (auto [index, speed] : zipper(speeds)) {
        if (speed.has_value()) {
            for (auto player : _players) {
                _speedUpdater(player.first, index, speed.value().x, speed.value().y);
            }
        }
    }

    for (auto [index, position] : zipper(pos)) {
        if (position.has_value()) {
            for (auto player: _players) {
                _positionUpdater(player.second, index, position.value().x, position.value().y);
            }
        }
    }
}
