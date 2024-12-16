/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Health
*/

#include "Health.hpp"

Health::Health(int health)
    : _health(health)
{
}

Health::~Health()
{
}

void Health::setHealth(int health)
{
    _health = health;
}

int Health::getHealth()
{
    return _health;
}
