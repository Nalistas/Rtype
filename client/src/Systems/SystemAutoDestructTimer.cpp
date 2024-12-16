/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAutoDestructTimer
*/

#include "Systems/SystemAutoDestructTimer.hpp"
#include "registry.hpp"
#include <chrono>

SystemAutoDestructTimer::SystemAutoDestructTimer()
{
}

SystemAutoDestructTimer::~SystemAutoDestructTimer()
{
}

void SystemAutoDestructTimer::operator()(ecs::registry &registry, ecs::entity const &e, AutoDestructTimer &auto_destruct_timer)
{
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now()
    ).time_since_epoch().count();

    if (static_cast<long int>(auto_destruct_timer.get_created_time() + auto_destruct_timer.get_time_to_destruct()) < now) {
            registry.delete_entity(e);
    }
}
