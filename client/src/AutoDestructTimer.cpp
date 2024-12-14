/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** AutoDestructTimer
*/

#include "AutoDestructTimer.hpp"
#include <ctime>

AutoDestructTimer::AutoDestructTimer()
{
}

AutoDestructTimer::~AutoDestructTimer()
{
}

void AutoDestructTimer::set_time_to_destruct(std::size_t time_to_destruct)
{
    _time_to_destruct = time_to_destruct;
}

void AutoDestructTimer::set_created_time(std::size_t created_time)
{
    _created_time = created_time;
}

std::size_t AutoDestructTimer::get_time_to_destruct()
{
    return _time_to_destruct;
}

std::size_t AutoDestructTimer::get_created_time()
{
    return _created_time;
}
