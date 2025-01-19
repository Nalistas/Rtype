/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** SystemMovement
*/

#include "Systems/SystemMovement.hpp"
#include "zipper.hpp"
#include <chrono>

using namespace std::chrono;

SystemMovement::SystemMovement()
{
    _ms_last_update = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

SystemMovement::~SystemMovement()
{
}

void SystemMovement::operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Speed> &speeds)
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto time_elapsed = millisec_since_epoch - _ms_last_update;

    if (time_elapsed < 10) {
        return;
    }
    std::cout << "GOGOOGOGOGOGOGOGOGOGOGOG" << std::endl;
    for (auto [index, position, speed] : zipper(positions, speeds)) {
        if (position.has_value() && speed.has_value()) {
            std::cout << "index: " << index << " x: " << position.value().x << " y: " << position.value().y << std::endl;
            position.value().x += speed.value().x * (time_elapsed / 10);
            position.value().y += speed.value().y * (time_elapsed / 10);
            std::cout << "speed: " << speed.value().x << " " << speed.value().y << std::endl;
            std::cout << "index: " << index << " x: " << position.value().x << " y: " << position.value().y << std::endl;
        }
    }
    _ms_last_update = millisec_since_epoch;
}
