/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemBackground
*/

#include "Systems/SystemBackground.hpp"

SystemBackground::SystemBackground(std::size_t const &elpased_time) :
    _elpased_time(elpased_time)
{
}

SystemBackground::~SystemBackground()
{
}

#include <iostream>


void SystemBackground::operator()(ecs::registry &r __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Background &b)
{
    b.update_position(_elpased_time);
    b.draw();
}
