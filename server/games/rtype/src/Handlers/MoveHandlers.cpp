/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "Handlers/MoveHandlers.hpp"
#include "Component/Position.hpp"

#include <iostream>

UpHandlers::UpHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_map<std::size_t, std::size_t> const &players)
    : _registry(reg), _players(players) {}

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

ShootHandlers::ShootHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

ShootHandlers::~ShootHandlers() {}

void ShootHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Shoot: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto bullet = _registry->create_entity();
    auto player = _registry->get_components<Position>()[client];
    _registry->get_components<Position>().insert_at(bullet, Position{player.value().x + 35, player.value().y});
    _registry->get_components<Speed>().insert_at(bullet, Speed{1, 0});
    _registry->get_components<Hitbox>().insert_at(bullet, Hitbox{1, 1});
    _registry->get_components<Damage>().insert_at(bullet, Damage{1});
    _registry->get_components<SIDE>().insert_at(bullet, SIDE::PLAYER);

    // broadcast to all players
}
