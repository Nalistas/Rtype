/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** SystemMovement
*/

#include "Systems/SystemMovement.hpp"
#include "zipper.hpp"
#include "IGame.hpp"
#include "registry.hpp"
#include <chrono>
#include <unordered_map>

using namespace std::chrono;

SystemMovement::SystemMovement(std::unordered_map<std::size_t, std::size_t> &players, rtype::IGame::Deleter const &deleter, bool &lose) :
    _players(players), _deleter(deleter), _lose(lose)
{
    _ms_last_update = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

SystemMovement::~SystemMovement()
{
}

bool SystemMovement::isAPlayerEntity(std::size_t entity)
{
    return _players.find(entity) != _players.end();
}

void SystemMovement::operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Speed> &speeds)
{
    if (_lose) {
        return;
    }
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto time_elapsed = millisec_since_epoch - _ms_last_update;

    if (time_elapsed < 16) {
        return;
    }
    for (auto [index, position, speed] : zipper(positions, speeds)) {
        if (!position.has_value() || !speed.has_value()) {
            continue;
        }
        position.value().x += (speed.value().x * time_elapsed / 10);
        position.value().y += (speed.value().y * time_elapsed / 10);
        if (isAPlayerEntity(index)) {
            if (position.value().x < 0) {
                position.value().x = 0;
                speed.value().x = 0;
            } if (position.value().y < 0) {
                position.value().y = 0;
                speed.value().y = 0;
            } if (position.value().x > 800) {
                position.value().x = 800;
                speed.value().x = 0;
            } if (position.value().y > 600) {
                position.value().y = 600;
                speed.value().y = 0;
            }
            continue;
        }
        if (position.value().x < 0 || position.value().y < 0 || position.value().x > 1000 || position.value().y > 1000) {
            for (auto player : _players) {
                _deleter(player.first, index);
            }
            registry.delete_entity(registry.entity_from_index(index));
        }
    }
    _ms_last_update = millisec_since_epoch;
}
