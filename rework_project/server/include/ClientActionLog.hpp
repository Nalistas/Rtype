/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** ClientActionLog
*/

#include "IGame.hpp"
#include <memory>
#include <chrono>
#include <functional>
#include <optional>

#ifndef CLIENTACTIONLOG_HPP_
    #define CLIENTACTIONLOG_HPP_

class ClientActionLog {

    public:
        ClientActionLog(
            std::vector<std::shared_ptr<rtype::IClientActionHandler>> &handlers,
            std::unordered_map<std::string, size_t> const &players,
            std::function<void(std::size_t client_id)> const &update_screen
        );
        ~ClientActionLog();

        std::optional<std::function<void()>> treatAction(std::string const &client_ip, std::vector<uint8_t> const &message);

    private:

        uint32_t decodeUint32(std::vector<uint8_t> const &vec, std::size_t pos) const;

        std::vector<std::shared_ptr<rtype::IClientActionHandler>> &_handlers;
        std::unordered_map<std::string, std::chrono::milliseconds> _players_time;
        std::function<void(std::size_t client_id)> const &_update_screen;
        std::unordered_map<std::string, std::size_t> const &_players;
};

#endif /* !CLIENTACTIONLOG_HPP_ */
