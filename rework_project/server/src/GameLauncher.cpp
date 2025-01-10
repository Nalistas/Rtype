/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameLauncher
*/

#include "GameLauncher.hpp"

GameLauncher::GameLauncher(std::string const &game_path)
{
    _loader.open(game_path);
    _game = _loader.getSym("entry_point");
}

GameLauncher::~GameLauncher()
{
}
