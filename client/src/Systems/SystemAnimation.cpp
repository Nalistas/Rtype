/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAnimation
*/

#include "Systems/SystemAnimation.hpp"

SystemAnimation::SystemAnimation(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemAnimation::~SystemAnimation()
{
}

void SystemAnimation::operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Animation &animation, raylib::Sprite &sprite)
{
    // animation.
    sprite.set_offset(animation.getSourceRect().x, animation.getSourceRect().y);
}