/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameLauncher
*/

#include "GameLauncher.hpp"
#include "RessourcesManager.hpp"
#include "GameCore.hpp"

GameLauncher::GameLauncher(std::string const &game_path)
{
    _loader.open(game_path);
    _game = _loader.getSym("entry_point");
    RessourcesManager rm(_game);
    _ressources = rm.getRessourcess();
}

GameLauncher::~GameLauncher()
{
    _game.reset();
    _loader.close();
}

std::list<std::vector<char>> const &GameLauncher::getRessources()
{
    return _ressources;
}

std::string GameLauncher::getIp()
{
    return _server.getEndpoint().address().to_string();
}

uint16_t GameLauncher::getPort()
{
    return _server.getEndpoint().port();
}

GameCore::ServerActions GameLauncher::getServerActions()
{
    return { []() { std::cout << "Action serveur exécutée !" << std::endl; } };
}

void GameLauncher::launch(std::list<Player> const &players)
{
    this->_game->initGameRegistry(this->_registry);
    auto get_action = [this]() { return this->getServerActions(); };

    GameCore core(this->_registry, get_action);
    core.run();
}
