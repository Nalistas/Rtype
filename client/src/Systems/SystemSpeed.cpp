// /*
// ** EPITECH PROJECT, 2024
// ** mirror-rtype
// ** File description:
// ** SystemSpeed
// */

#include "Systems/SystemSpeed.hpp"
#include <iostream>

SystemSpeed::SystemSpeed(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemSpeed::~SystemSpeed()
{
}

// #include <iostream>

void SystemSpeed::operator()(ecs::registry &registry, ecs::entity const &e, Speed &speed, raylib::Sprite &sprite)
{
    raylib::Vector2 pos = sprite.get_position();

    (void)registry;
    (void)e;
    pos.x += speed.getSpeed().x * (static_cast<float>(this->_elpased_time) / 10.0f);
    pos.y += speed.getSpeed().y * (static_cast<float>(this->_elpased_time) / 10.0f);
    std::cout << "Speed: " << speed.getSpeed().x << " " << speed.getSpeed().y << std::endl;
    sprite.set_position(pos.x, pos.y);
}
