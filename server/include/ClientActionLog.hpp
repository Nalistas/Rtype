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
        /**
         * @brief Constructor for ClientActionLog.
         *
         * @param handlers A vector of ClientActionHandler to handle client actions.
         * @param players A map of player IP to player ID.
         * @param update_screen A function to call when the screen for a client
         *                      needs to be updated. It takes a single argument:
         *                      the client ID.
         */
        ClientActionLog(
            std::vector<std::shared_ptr<rtype::IClientActionHandler>> &handlers,
            std::unordered_map<std::string, size_t> const &players,
            std::function<void(std::size_t)> const &update_screen
        );

        /**
         * @brief Destructor for ClientActionLog.
         */
        ~ClientActionLog();

        /**
         * @brief Treats an action from a client.
         *
         * @param client_ip The IP address of the client.
         * @param message The message received from the client.
         * @return An optional function to call. There might be action from
         *         the client that does not require the call of a function.
         */
        std::optional<std::function<void()>> treatAction(std::string const &client_ip, std::vector<uint8_t> const &message);

    private:

        /**
         * @brief Decodes a 32-bit unsigned integer from a vector of bytes.
         *
         * @param vec The vector of bytes to decode.
         * @param pos The position in the vector to start decoding.
         * @return The decoded 32-bit unsigned integer.
         */
        uint32_t decodeUint32(std::vector<uint8_t> const &vec, std::size_t pos) const;

        std::vector<std::shared_ptr<rtype::IClientActionHandler>> &_handlers;
        std::unordered_map<std::string, std::chrono::milliseconds> _players_time;
        std::unordered_map<std::string, std::size_t> const &_players;
        std::function<void(std::size_t)> const &_update_screen;
};

#endif /* !CLIENTACTIONLOG_HPP_ */
