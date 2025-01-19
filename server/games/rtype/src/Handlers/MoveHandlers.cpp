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
    auto &position = _registry->get_components<Position>()[client];
    std::cout << "player: " << client << std::endl;
    if (position.has_value()) {
        // _registry->get_components<Position>().emplace_at(client, Position{position.value().x, position.value().y - 10});
        std::cout << "player: " << client << " x: " << position.value().x << " y: " << position.value().y << std::endl;
        position.value().y -= 10;
        std::cout << "player: " << client << " x: " << position.value().x << " y: " << position.value().y << std::endl;
    }
    std::cout << client << std::endl;
    std::cout << _registry << std::endl;
    // std::cout << "handler Up: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    // auto position = _registry->get_components<Position>();
    // std::cout << "coucou" << std::endl;
    // for (auto [index, pos] : zipper(position)) {
    //     std::cout << "coucou index " << index << std::endl;
    //     if (pos.has_value()) {
    //         std::cout << "index " << index << " has pos !" << std::endl;
    //         pos.value().y -= 1;
    //     }
    // }
}

DownHandlers::DownHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

DownHandlers::~DownHandlers() {}

void DownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    std::cout << "handler Down: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto &player = _registry->get_components<Position>()[client];
    if (player.has_value()) {
        std::cout << "player: " << client << " x: " << player.value().x << " y: " << player.value().y << std::endl;
        player.value().y += 10;
        std::cout << "player: " << client << " x: " << player.value().x << " y: " << player.value().y << std::endl;
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
    auto &player = _registry->get_components<Position>()[client];
    if (player.has_value()) {
        std::cout << "player: " << client << " x: " << player.value().x << " y: " << player.value().y << std::endl;
        player.value().x -= 10;
        std::cout << "player: " << client << " x: " << player.value().x << " y: " << player.value().y << std::endl;
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
    std::cout << "handler Right: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    auto &player = _registry->get_components<Position>()[client];
    if (player.has_value()) {
        player.value().x += 10;
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
