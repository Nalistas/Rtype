/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GameLauncherUdpProtocol
*/

#include "GameLauncher.hpp"

void GameLauncher::speedUpdater(std::size_t player_id, std::size_t e_id, uint8_t speed_x, uint8_t speed_y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(5);

    data[0] = 4;
    data[1] = (e_id / 256) & 0xFF;
    data[2] = e_id & 0xFF;
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
    data[1] = (e_id16 / 256) & 0xFF;
    data[2] = e_id16 & 0xFF;
    data[3] = (x / 16777216) & 0xFF;
    data[4] = (x / 65536) & 0xFF;
    data[5] = (x / 256) & 0xFF;
    data[6] = x & 0xFF;
    data[7] = (y / 16777216) & 0xFF;
    data[8] = (y / 65536) & 0xFF;
    data[9] = (y / 256) & 0xFF;
    data[10] = y & 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::creater(std::size_t player_id, std::size_t e_id, std::size_t e_g_id, int x, int y, uint8_t speed_x, uint8_t speed_y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        std::cout << "player not found" << std::endl;
        return;
    }
    std::vector<uint8_t> data(14);
    data[0] = 2;
    data[1] = e_g_id & 0xFF;
    data[2] = (e_id / 256) & 0xFF;
    data[3] = e_id & 0xFF;
    data[4] = (x / 16777216) & 0xFF;
    data[5] = (x / 65536) & 0xFF;
    data[6] = (x / 256) & 0xFF;
    data[7] = x & 0xFF;
    data[8] = (y / 16777216) & 0xFF;
    data[9] = (y / 65536) & 0xFF;
    data[10] = (y / 256) & 0xFF;
    data[11] = y & 0xFF;
    data[12] = speed_x;
    data[13] = speed_y;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::deleter(std::size_t player_id, std::size_t e_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 3;
    data[1] = (e_id / 256) & 0xFF;
    data[2] = e_id & 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::backgroundChanger(std::size_t player_id, std::size_t background_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 1;
    data[1] = (background_id / 256) & 0xFF;
    data[2] = background_id & 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::musicChanger(std::size_t player_id, std::size_t music_id)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(3);
    data[0] = 6;
    data[1] = (music_id / 256) & 0xFF;
    data[2] = music_id & 0xFF;
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}

void GameLauncher::textChanger(std::size_t player_id, uint8_t text_id, std::string const &text, uint8_t size, uint32_t x, uint32_t y)
{
    if (_players_endpoints.find(player_id) == _players_endpoints.end()) {
        return;
    }
    std::vector<uint8_t> data(11 + text.size());

    data[0] = 7;
    data[1] = text_id;
    data[2] = size;
    data[3] = (x / 16777216) & 0xFF;
    data[4] = (x / 65536) & 0xFF;
    data[5] = (x / 256) & 0xFF;
    data[6] = x & 0xFF;
    data[7] = (y / 16777216) & 0xFF;
    data[8] = (y / 65536) & 0xFF;
    data[9] = (y / 256) & 0xFF;
    data[10] = y & 0xFF;
    std::copy(text.begin(), text.end(), data.begin() + 11);
    this->_server.sendTo(_players_endpoints.at(player_id), data);
}
