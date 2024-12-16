/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemTime
*/

#include "Systems/SystemTime.hpp"
#include <chrono>
#include <iostream>

SystemTime::SystemTime(std::size_t &time_to_update) :
    _last_update(std::chrono::system_clock::now()), _elpased_time(time_to_update)
{
}

SystemTime::~SystemTime()
{
}

void SystemTime::operator()(ecs::registry &r __attribute__((unused)), ecs::entity const &e __attribute__((unused)))
{
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_update).count();

    if (elapsed < 5) {
        _elpased_time = 0;
        return;
    }
    _elpased_time = elapsed;
    this->_last_update = now;
}
