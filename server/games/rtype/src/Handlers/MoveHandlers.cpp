/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "Handlers/MoveHandlers.hpp"
#include "Component/Position.hpp"

#include <iostream>

UpHandlers::UpHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

UpHandlers::~UpHandlers() {}

void UpHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().y = -2;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{0, -2});
    }
}

DownHandlers::DownHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

DownHandlers::~DownHandlers() {}

void DownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];

    if (speed.has_value()) {
        speed.value().y = 2;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{0, 2});
    }
}

LeftHandlers::LeftHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

LeftHandlers::~LeftHandlers() {}

void LeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
     if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }

    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().x = -2;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{-2, 0});
    }
}

RightHandlers::RightHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

RightHandlers::~RightHandlers() {}

void RightHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];

    if (speed.has_value()) {
        speed.value().x = 2;
    } else {
        _registry->get_components<Speed>().emplace_at(client, Speed{2, 0});
    }
}


UnRightLeftHandlers::UnRightLeftHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

UnRightLeftHandlers::~UnRightLeftHandlers() {}

void UnRightLeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().x = 0;
    }
}

UnUpDownHandlers::UnUpDownHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads) : _registry(reg), _deads(deads) {}

UnUpDownHandlers::~UnUpDownHandlers() {}

void UnUpDownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    if (_deads.find(client) != _deads.end()) {
        return;
    }
    auto &speed = _registry->get_components<Speed>()[client];
    if (speed.has_value()) {
        speed.value().y = 0;
    }
}
