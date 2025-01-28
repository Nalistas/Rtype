/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** ClientActionLog
*/

#include "ClientActionLog.hpp"
#include <iostream>

ClientActionLog::ClientActionLog(
    std::vector<std::shared_ptr<rtype::IClientActionHandler>> &handlers,
    std::unordered_map<std::string, std::size_t> const &players,
    std::function<void(std::size_t)> const &update_screen
) :
    _handlers(handlers), _players(players), _update_screen(update_screen)
{
    for (auto const &player : players) {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );
        _players_time[player.first] = now;
    }
}

ClientActionLog::~ClientActionLog()
{
}

std::optional<std::function<void()>> ClientActionLog::treatAction(std::string const &client_ip, std::vector<uint8_t> const &message)
{
    auto it = _players.find(client_ip);
    if (it == _players.end()) {
        return std::nullopt;
    }
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
    _players_time[client_ip] = now;

    std::size_t player_id = it->second;

    if (message[0] == 1) {
        if (message.size() < 13) {
            std::cout << "invalid message size: " << message.size() << std::endl;
            return std::nullopt;
        }
        uint32_t action_id = decodeUint32(message, 1);

        if (action_id >= _handlers.size()) {
            std::cout << "invalid action id: " << action_id << std::endl;
            return std::nullopt;
        }

        uint32_t mouse_x = decodeUint32(message, 5);
        uint32_t mouse_y = decodeUint32(message, 9);

        return std::optional<std::function<void()>>([this, player_id, action_id, mouse_x, mouse_y](){
            (*_handlers[action_id])(player_id, mouse_x, mouse_y);
        });
    }
    if (message[0] == 2) {
        return std::optional<std::function<void()>>([this, player_id](){
            // std::cout << "player need to be updated: " << player_id << std::endl;
            this->_update_screen(player_id);
        });
    }
    return std::nullopt;
}

uint32_t ClientActionLog::decodeUint32(std::vector<uint8_t> const &vec, std::size_t pos) const
{
    return (static_cast<uint32_t>(static_cast<unsigned char>(vec[pos])) * 16777216) +
           (static_cast<uint32_t>(static_cast<unsigned char>(vec[pos + 1])) * 65536) +
           (static_cast<uint32_t>(static_cast<unsigned char>(vec[pos + 2])) * 256) +
           static_cast<uint32_t>(static_cast<unsigned char>(vec[pos + 3]));
}
