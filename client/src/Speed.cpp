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

Vector2 Speed::getSpeed()
{
    return _speed;
}

void Speed::setSpeed(Vector2 speed)
{
    _speed = speed;
}
