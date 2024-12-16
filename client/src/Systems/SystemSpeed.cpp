// /*
// ** EPITECH PROJECT, 2024
// ** mirror-rtype
// ** File description:
// ** SystemSpeed
// */

#include "Systems/SystemSpeed.hpp"
#include <iostream>
#include <cmath>

SystemSpeed::SystemSpeed(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemSpeed::~SystemSpeed()
{
}

void SystemSpeed::operator()(ecs::registry &registry, ecs::entity const &e, Speed &speed, raylib::Sprite &sprite)
{
    raylib::Vector2 pos = sprite.get_position();

    (void)registry;
    (void)e;
    pos.x += static_cast<int>(speed.getSpeed().x) * (static_cast<float>(this->_elpased_time) / 10.0f);
    pos.y += static_cast<int>(speed.getSpeed().y) * (static_cast<float>(this->_elpased_time) / 10.0f);
    pos.x = static_cast<int>(std::round(pos.x));
    pos.y = static_cast<int>(std::round(pos.y));
    sprite.set_position(pos.x, pos.y);
    // std::cout << "e: " << e << " : " << pos.x << " " << pos.y << " with speed: " << speed.getSpeed().x << " " << speed.getSpeed().y << std::endl;
}
