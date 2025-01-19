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
        for (auto it : data) {
            printf("%02hhd ", it);
        }
        printf("\n");
        std::string endpoint_to_string = endpoint.address().to_string() + std::to_string(endpoint.port());
        std::cout << "endpoint_to_string: " << endpoint_to_string << std::endl;
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

void GameLauncher::speedUpdater(std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(5);

    data[0] = 4;
    data[1] = (e_id / 256) && 0xFF;
    data[2] = e_id && 0xFF;
    data[3] = speed_x;
    data[4] = speed_y;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::positionUpdater(std::size_t player_id, std::size_t e_id, int x, int y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    uint16_t e_id16 = static_cast<uint16_t>(e_id);
    std::vector<uint8_t> data(11);

    data[0] = 5;
    data[1] = (e_id16 / 256) && 0xFF;
    data[2] = e_id16 && 0xFF;
    data[3] = (x / 16777216) && 0xFF;
    data[4] = (x / 65536) && 0xFF;
    data[5] = (x / 256) && 0xFF;
    data[6] = x && 0xFF;
    data[7] = (y / 16777216) && 0xFF;
    data[8] = (y / 65536) && 0xFF;
    data[9] = (y / 256) && 0xFF;
    data[10] = y && 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::creater(std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(14);
    data[0] = 2;
    data[1] = e_g_id && 0xFF;
    data[2] = (e_id / 256) && 0xFF;
    data[3] = e_id && 0xFF;
    data[4] = (x / 16777216) && 0xFF;
    data[5] = (x / 65536) && 0xFF;
    data[6] = (x / 256) && 0xFF;
    data[7] = x && 0xFF;
    data[8] = (y / 16777216) && 0xFF;
    data[9] = (y / 65536) && 0xFF;
    data[10] = (y / 256) && 0xFF;
    data[11] = y && 0xFF;
    data[12] = speed_x;
    data[13] = speed_y;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::Deleter(std::size_t player_id, std::size_t e_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 3;
    data[1] = (e_id / 256) && 0xFF;
    data[2] = e_id && 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::BackgroundChanger(std::size_t player_id, std::size_t background_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 1;
    data[1] = (background_id / 256) && 0xFF;
    data[2] = background_id && 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::MusicChanger(std::size_t player_id, std::size_t music_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 6;
    data[1] = (music_id / 256) && 0xFF;
    data[2] = music_id && 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::launch()
{
    this->_game->setCreate([this](std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y) {
        this->creater(player_id, e_id, e_g_id, x, y, speed_x, speed_y);
    });
    this->_game->setDelete([this](std::size_t player_id, std::size_t e_id) { this->Deleter(player_id, e_id); });
    this->_game->setUpdatePosition([this](std::size_t player_id, std::size_t e_id, int x, int y) { this->positionUpdater(player_id, e_id, x, y); });
    this->_game->setUpdateSpeed([this](std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y) { this->speedUpdater(player_id, e_id, speed_x, speed_y); });
    this->_game->setUseBackground([this](std::size_t client_id, std::size_t background_id) { this->BackgroundChanger(client_id, background_id); });
    this->_game->setUseMusic([this](std::size_t client_id, std::size_t music_id) { this->MusicChanger(client_id, music_id); });
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
