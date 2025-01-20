/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** SystemMovement
*/

#include "isystem.hpp"
#include "sparse_array.hpp"
#include "Component/Position.hpp"
#include "IGame.hpp"
#include <unordered_map>
#include <cstdint>

#ifndef SYSTEMMOVEMENT_HPP_
    #define SYSTEMMOVEMENT_HPP_

class SystemMovement : public ecs::isystem<Position, Speed> {
    public:
        /**
         * @brief Construct a new SystemMovement object
         * 
         * @param players
         * @param deleter
         */
        SystemMovement(std::unordered_map<std::size_t, std::size_t> &players, rtype::IGame::Deleter const &deleter);
        ~SystemMovement();

        /**
         * @brief Update the speed and position of the player
         * 
         * @param registry
         * @param positions
         * @param speeds
         */
        void operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Speed> &speeds) override;
    private:
        /**
         * @brief Check if the entity is a player entity
         * 
         * @param entity 
         * @return true 
         * @return false
         */
        bool isAPlayerEntity(std::size_t entity);

        int64_t _ms_last_update;
        std::unordered_map<std::size_t, std::size_t> &_players;
        rtype::IGame::Deleter const &_deleter;

};

#endif /* !SYSTEMMOVEMENT_HPP_ */
