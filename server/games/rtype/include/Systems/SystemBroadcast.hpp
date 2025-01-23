/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemBroadcast
*/

#include "isystem.hpp"
#include "Component/Position.hpp"
#include "IGame.hpp"
#include <map>

#ifndef SYSTEMBROADCAST_HPP_
#define SYSTEMBROADCAST_HPP_

/**
 * @brief SystemBroadcast class to handle the broadcast of the speed and position of the player
 */
class SystemBroadcast : public ecs::isystem<Speed, Position> {
    public:
        /**
         * @brief Construct a new SystemBroadcast object
         * 
         * @param speedUpdater
         * @param positionUpdater
         * @param players
         */
        SystemBroadcast(rtype::IGame::SpeedUpdater &speedUpdater, rtype::IGame::PositionUpdater &positionUpdater, std::unordered_map<std::size_t, std::size_t> &players);
        ~SystemBroadcast();

        /**
         * @brief Update the speed and position of the player for all players
         */
        void operator()(ecs::registry &registry, sparse_array<Speed> &speed, sparse_array<Position> &pos) override;

    protected:
    private:
        rtype::IGame::SpeedUpdater _speedUpdater;
        rtype::IGame::PositionUpdater _positionUpdater;
        std::unordered_map<std::size_t, std::size_t> &_players;
        int64_t _ms_last_update;
        int64_t _ms_last_update_main;
};

#endif /* !SYSTEMBROADCAST_HPP_ */
