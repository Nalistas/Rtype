/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemTime
*/

#include "Systems/SystemTime.hpp"
#include <chrono>

SystemTime::SystemTime(std::size_t &time_to_update) :
    _last_update(std::chrono::system_clock::now()), _elpased_time(time_to_update)
{
}

SystemTime::~SystemTime()
{
}

void SystemTime::operator()(ecs::iregistry &r __attribute__((unused)))
{
    auto now = std::chrono::system_clock::now();
    _elpased_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_update).count();
}
