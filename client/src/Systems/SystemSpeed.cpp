// /*
// ** EPITECH PROJECT, 2024
// ** mirror-rtype
// ** File description:
// ** SystemSpeed
// */

// #include "Systems/SystemSpeed.hpp"

// SystemSpeed::SystemSpeed(std::size_t const &elpased_time) :
//     _elpased_time(elpased_time)
// {
// }

// SystemSpeed::~SystemSpeed()
// {
// }

// #include <iostream>

<<<<<<< HEAD
void SystemSpeed::operator()(ecs::registry &registry, ecs::entity const &e, Speed &speed, raylib::Sprite &sprite)
{
    raylib::Vector2 pos = sprite.get_position();

    (void)registry;
    (void)e;
    pos.x += speed.getSpeed().x * (static_cast<float>(this->_elpased_time) / 10.0f);
    pos.y += speed.getSpeed().y * (static_cast<float>(this->_elpased_time) / 10.0f);
    sprite.set_position(pos.x, pos.y);
    std::cout << this->_elpased_time << " " << pos.x << " " << pos.y << std::endl;
}
=======
// void SystemSpeed::operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, raylib::Sprite &sprite)
// {
//     raylib::Vector2 pos = sprite.get_position();

//     pos.x += speed.getSpeed().x * (static_cast<float>(this->_elpased_time) / 10.0f);
//     pos.y += speed.getSpeed().y * (static_cast<float>(this->_elpased_time) / 10.0f);
//     sprite.set_position(pos.x, pos.y);
//     std::cout << this->_elpased_time << " " << pos.x << " " << pos.y << std::endl;
// }
>>>>>>> bf06f69d2789240dfa24cadddcf76c9bc0fd6c4a
