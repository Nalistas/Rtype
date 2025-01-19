/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "Handlers/MoveHandlers.hpp"
#include "Component/Position.hpp"

#include <iostream>

UpHandlers::UpHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

UpHandlers::~UpHandlers() {}

void UpHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Up: " << client << " " << mouse_x << " " << mouse_y << std::endl;
    if (!_registry) {
        std::cout << "registry is null" << std::endl;
        return;
    }
    auto position = _registry->get_components<Position>();
    std::cout << "coucou" << std::endl;
    for (auto [index, pos] : zipper(position)) {
        std::cout << "coucou index " << index << std::endl;
        if (pos.has_value()) {
            std::cout << "index " << index << " has pos !" << std::endl;
            pos.value().y -= 1;
        }
    }
    std::cout << "handler Up: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

DownHandlers::DownHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

DownHandlers::~DownHandlers() {}

void DownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Down: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

LeftHandlers::LeftHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

LeftHandlers::~LeftHandlers() {}

void LeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Left: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

RightHandlers::RightHandlers(const std::shared_ptr<ecs::registry> &reg) : _registry(reg) {}

RightHandlers::~RightHandlers() {}

void RightHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Right: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}
