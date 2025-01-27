/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** ShootHandlers
*/

#include "Handlers/ShootHandlers.hpp"
#include "Component/Position.hpp"

#include <iostream>

ShootHandlers::ShootHandlers(const std::shared_ptr<ecs::registry> &reg, rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players, std::unordered_set<std::size_t> const &deads) :
    _registry(reg), _deads(deads), _creater(creater), _players(players) {}

ShootHandlers::~ShootHandlers() {}

void ShootHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto player = _registry->get_components<Position>()[client];
    auto bullet = _registry->create_entity();
    _registry->get_components<Position>().emplace_at(bullet, Position{player.value().x + 35, player.value().y});
    _registry->get_components<Speed>().emplace_at(bullet, Speed{2, 0});
    _registry->get_components<Hitbox>().emplace_at(bullet, Hitbox{1, 1});
    _registry->get_components<Damage>().emplace_at(bullet, Damage{1});
    _registry->get_components<SIDE>().emplace_at(bullet, SIDE::PLAYER);

    for (auto player : _players) {
        _creater(player.first, bullet, 2,
            _registry->get_components<Position>()[bullet].value().x,
            _registry->get_components<Position>()[bullet].value().y,
            _registry->get_components<Speed>()[bullet].value().x,
            _registry->get_components<Speed>()[bullet].value().y);
    }

    // broadcast to all players
}

