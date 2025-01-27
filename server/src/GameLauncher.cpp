/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameLauncher
*/

#include "GameLauncher.hpp"
#include "RessourcesManager.hpp"
#include "GameCore.hpp"

GameLauncher::GameLauncher(std::string const &game_path, int port) : _server(port)
{
    _registry = std::make_shared<ecs::registry>();
    std::cout << _registry << std::endl;
    _loader.open(game_path);
    _game = _loader.getSym("entry_point");
    std::cout << "///////////////////////////" << std::endl;
}

GameLauncher::~GameLauncher()
{
    _game.reset();
    _loader.close();
}

GameCore::ServerActions GameLauncher::getServerActions()
{
    if (this->_client_action_log == nullptr) {
        return {};
    }
    std::list<std::function<void()>> actions;

    while (_server.hasDataToRead()) {
        asio::ip::udp::endpoint endpoint;
        std::vector<uint8_t> data;
        _server.readFrom(endpoint, data);
        std::string endpoint_to_string = endpoint.address().to_string() + std::to_string(endpoint.port());
        if (_players.find(endpoint_to_string) == _players.end()) {
            std::cout << "new player added" << std::endl;
            auto playerId = this->_game->createPlayer();
            this->_players[endpoint_to_string] = playerId;
            this->_players_endpoints.emplace(playerId, endpoint);
        }
        auto action = this->_client_action_log->treatAction(endpoint_to_string, data);
        if (action.has_value()) {
            actions.push_back(action.value());
        } else {
            std::cout << "action not found !" << std::endl;
        }
    }
    return actions;
}


void GameLauncher::launch()
{
    this->_game->setCreate([this](std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y) {
        this->creater(player_id, e_id, e_g_id, x, y, speed_x, speed_y);
    });
    this->_game->setDelete([this](std::size_t player_id, std::size_t e_id) { this->deleter(player_id, e_id); });
    this->_game->setUpdatePosition([this](std::size_t player_id, std::size_t e_id, int x, int y) { this->positionUpdater(player_id, e_id, x, y); });
    this->_game->setUpdateSpeed([this](std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y) { this->speedUpdater(player_id, e_id, speed_x, speed_y); });
    this->_game->setUseBackground([this](std::size_t client_id, std::size_t background_id) { this->backgroundChanger(client_id, background_id); });
    this->_game->setUseMusic([this](std::size_t client_id, std::size_t music_id) { this->musicChanger(client_id, music_id); });
    this->_game->setTextUpdater([this](std::size_t client_id, uint8_t text_id, std::string const &text, uint8_t size, uint32_t x, uint32_t y) { this->textChanger(client_id, text_id, text, size, x, y);});
    this->_game->initGameRegistry(this->_registry);
    auto game_player_input_handler = _game->getClientActionHandlers();
    _handlers.resize(game_player_input_handler.size());
    int i = 0;

    std::cout << "size : " << game_player_input_handler.size() << std::endl;
    for (auto &handler : game_player_input_handler) {
        _handlers[i] = handler.handler;
        std::cout << "handler nb: " << i << std::endl;
        i++;
    }
    auto screen_updater = this->_game->getScreenUpdater();
    auto get_action = [this]() { return this->getServerActions(); };

    this->_client_action_log = std::make_unique<ClientActionLog>(this->_handlers, this->_players, screen_updater);
    GameCore core(this->_registry, get_action, screen_updater);
    core.run();
}
