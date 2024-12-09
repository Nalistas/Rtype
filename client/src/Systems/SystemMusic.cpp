/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemMusic
*/

#include "SystemMusic.hpp"

SystemMusic::SystemMusic()
{
}

SystemMusic::~SystemMusic()
{
}

void SystemMusic::operator()(ecs::registry &r, ecs::entity const &e, raylib::RayMusic &m)
{
    (void)r;
    (void)e;
    m.play();
}
