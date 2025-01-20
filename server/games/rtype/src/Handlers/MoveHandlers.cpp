/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "Handlers/MoveHandlers.hpp"
#include "Component/Position.hpp"

#include <iostream>

UpHandlers::UpHandlers(const std::shared_ptr<ecs::registry> &reg)
    : _registry(reg) {}

UpHandlers::~UpHandlers() {}

void UpHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Left: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().y = -1;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{0, -1});
    }
}

DownHandlers::DownHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

DownHandlers::~DownHandlers() {}

void DownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Left: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().y = 1;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{0, 1});
    }
}

LeftHandlers::LeftHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

LeftHandlers::~LeftHandlers() {}

void LeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Left: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().x = -1;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{-1, 0});
    }
}

RightHandlers::RightHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

RightHandlers::~RightHandlers() {}

void RightHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().x = 1;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{1, 0});
    }
}



UnRightLeftHandlers::UnRightLeftHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

UnRightLeftHandlers::~UnRightLeftHandlers() {}

void UnRightLeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().x = 0;
    }
}

UnUpDownHandlers::UnUpDownHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

UnUpDownHandlers::~UnUpDownHandlers() {}

void UnUpDownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().y = 0;
    }
}


ShootHandlers::ShootHandlers(const std::shared_ptr<ecs::registry> &reg, rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players) : _registry(reg), _creater(creater), _players(players) {}

ShootHandlers::~ShootHandlers() {}

void ShootHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Shoot: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto bullet = _registry->create_entity();
    std::cout << "bullet: " << bullet << std::endl;
    auto player = _registry->get_components<Position>()[client];
    _registry->get_components<Position>().emplace_at(bullet, Position{player.value().x + 35, player.value().y});
    _registry->get_components<Speed>().emplace_at(bullet, Speed{1, 0});
    _registry->get_components<Hitbox>().emplace_at(bullet, Hitbox{1, 1});
    _registry->get_components<Damage>().emplace_at(bullet, Damage{1});
    _registry->get_components<SIDE>().emplace_at(bullet, SIDE::PLAYER);

    std::cout << std::endl;
    std::cout << std::endl;
    for (auto player : _players) {
        std::cout << "player: " << player.first << std::endl;
        std::cout << "sending entity " << bullet << " to player " << player.first << std::endl;
        _creater(player.first, bullet, 2,
            _registry->get_components<Position>()[bullet].value().x,
            _registry->get_components<Position>()[bullet].value().y,
            _registry->get_components<Speed>()[bullet].value().x,
            _registry->get_components<Speed>()[bullet].value().y);
    }

    // broadcast to all players
}
