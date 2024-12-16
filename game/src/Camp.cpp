/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Camp
*/

#include "Camp.hpp"

Camp::Camp(bool enemy)
    : enemy(enemy)
{
}

Camp::~Camp()
{
}

bool Camp::getCamp()
{
    return enemy;
}

void Camp::setCamp(bool enemy)
{
    this->enemy = enemy;
}
