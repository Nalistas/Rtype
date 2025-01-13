/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::run(void)
{
    while (_window.is_running())
    {
        _window.start_drawing();
        _window.end_drawing();
    }
    
}
