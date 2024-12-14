/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** RtypeEnemy
*/

#include "RtypeEnemy.hpp"

RtypeEnemy::RtypeEnemy(): _position(0, 0), _speed(0, 0), _health(10)
{
}

RtypeEnemy::~RtypeEnemy()
{
}

const std::pair<std::size_t, std::size_t> &RtypeEnemy::getPosition(void) const
{
    return _position;
}

void RtypeEnemy::setPosition(std::size_t x, std::size_t y)
{
     _position = {x, y};
}

const std::pair<std::size_t, std::size_t> &RtypeEnemy::getSpeed(void) const
{
    return _speed;
}

void RtypeEnemy::setSpeed(std::size_t x, std::size_t y)
{
    _speed.first = x;
    _speed.second = y;
}

void RtypeEnemy::setHealth(std::size_t health)
{
    _health = health;
}

size_t RtypeEnemy::getHealth(void) const
{
    return _health;
}
