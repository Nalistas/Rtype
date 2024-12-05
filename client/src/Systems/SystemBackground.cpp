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


void SystemBackground::operator()(ecs::iregistry &r __attribute__((unused)), Background &b)
{
    std::cout << "elapsed time: " << _elpased_time << std::endl;
    b.update_position(_elpased_time);
    b.draw();
}
