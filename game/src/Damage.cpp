/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Damage
*/

#include "Damage.hpp"

Damage::Damage(int damage)
    : _damage(damage)
{
}

Damage::~Damage()
{
}

void Damage::setDamage(int damage)
{
    _damage = damage;
}

int Damage::getDamage()
{
    return _damage;
}
