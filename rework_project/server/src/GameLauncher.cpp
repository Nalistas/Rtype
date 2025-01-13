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
    auto game_player_input_handler = _game->getClientActionHandlers();
    _handlers.resize(game_player_input_handler.size());
    int i = 0;

    std::cout << "size : " << game_player_input_handler.size() << std::endl;
    for (auto &handler : game_player_input_handler) {
        _handlers[i] = handler.handler;
        std::cout << "handler nb: " << i << std::endl;
        i++;
    }
}

GameLauncher::~GameLauncher()
{
    _game.reset();
    _loader.close();
}

std::list<std::vector<uint8_t>> const &GameLauncher::getRessources()
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
    if (!_server.hasDataToRead() || this->_client_action_log == nullptr) {
        return {};
    }

    std::list<std::function<void()>> actions;

    while (_server.hasDataToRead()) {
        asio::ip::udp::endpoint endpoint;
        std::vector<uint8_t> data;
        _server.readFrom(endpoint, data);
        for (auto it : data) {
            printf("%02hhd ", it);
        }
        printf("\n");
        auto action = this->_client_action_log->treatAction(endpoint.address().to_string(), data);
        if (action.has_value()) {
            std::cout << "action found !" << std::endl;
            actions.push_back(action.value());
        } else {
            std::cout << "action not found !" << std::endl;
        }
    }
    return actions;
}

void GameLauncher::launch(std::list<Player> const &players)
{
    this->_game->initGameRegistry(this->_registry);
    auto get_action = [this]() { return this->getServerActions(); };
    auto screen_updater = this->_game->getScreenUpdater();

    for (auto const &player : players) {
        std::size_t player_id = this->_game->createPlayer();
        this->_players[player.ip] = player_id;
    }
    this->_client_action_log = std::make_unique<ClientActionLog>(this->_handlers, this->_players, screen_updater);

    GameCore core(this->_registry, get_action);
    core.run();
}
