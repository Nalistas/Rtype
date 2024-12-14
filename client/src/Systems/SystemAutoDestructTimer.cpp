/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAutoDestructTimer
*/

#include "SystemAutoDestructTimer.hpp"

SystemAutoDestructTimer::SystemAutoDestructTimer()
{
}

SystemAutoDestructTimer::~SystemAutoDestructTimer()
{
}

void SystemAutoDestructTimer::operator()(ecs::registry &registry, ecs::entity const &e, AutoDestructTimer &auto_destruct_timer)
{
    if (auto_destruct_timer.get_created_time() + auto_destruct_timer.get_time_to_destruct() < std::time(0)) {
        registry.remove_entity(e);
    }
}
