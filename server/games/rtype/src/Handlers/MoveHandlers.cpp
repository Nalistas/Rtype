/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "Handlers/MoveHandlers.hpp"

#include <iostream>

UpHandlers::UpHandlers() {}

UpHandlers::~UpHandlers() {}

void UpHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Up: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

DownHandlers::DownHandlers() {}

DownHandlers::~DownHandlers() {}

void DownHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Down: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

LeftHandlers::LeftHandlers() {}

LeftHandlers::~LeftHandlers() {}

void LeftHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Left: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}

RightHandlers::RightHandlers() {}

RightHandlers::~RightHandlers() {}

void RightHandlers::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    std::cout << "handler Right: " << client << " " << mouse_x << " " << mouse_y << std::endl;
}
