/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Speed
*/

#include "Speed.hpp"

Speed::Speed()
{
}

Speed::~Speed()
{
}

raylib::Vector2 Speed::getSpeed()
{
    return _speed;
}

void Speed::setSpeed(raylib::Vector2 speed)
{
    _speed = speed;
}
