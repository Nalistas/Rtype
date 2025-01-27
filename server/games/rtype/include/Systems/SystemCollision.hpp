/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "isystem.hpp"
#include "Component/Position.hpp"
#include "IGame.hpp"
#include <unordered_set>

#ifndef SYSTEMCOLLISION_HPP_
#define SYSTEMCOLLISION_HPP_

/**
 * @brief SystemCollision class to handle the collision between entities
 */
class SystemCollision : public ecs::isystem<Position, Hitbox, Damage, Life, SIDE> {
    public:
        /**
         * @brief Construct a new SystemCollision object
         * 
         * @param deleter
         * @param players
         */
        SystemCollision(rtype::IGame::Deleter const &deleter, std::unordered_map<std::size_t, std::size_t> &players, std::unordered_set<std::size_t> &deads, rtype::IGame::LifeUpdater const &updater);
        ~SystemCollision();

        /**
         * @brief Update the speed and position of the player
         * 
         * @param registry
         * @param speed
         * @param position
         */
        void operator()(ecs::registry &registry, sparse_array<Position> &position, sparse_array<Hitbox> &hitbox, sparse_array<Damage> &damage, sparse_array<Life> &health, sparse_array<SIDE> &side);

        /**
         * @brief Check if two entities are colliding
         * 
         * @param posA 
         * @param hitboxA 
         * @param posB 
         * @param hitboxB 
         * @return true 
         * @return false
         */
        bool checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB);

    private:
        /**
         * @brief Broadcast the deletion of an entity
         * 
         * @param entity_deleted
         */
        void broadcast(std::size_t entity_deleted, ecs::registry &registry);


        rtype::IGame::Deleter const &_deleter;
        rtype::IGame::LifeUpdater const &_updater;
        std::unordered_map<std::size_t, std::size_t> &_players;
        std::unordered_set<std::size_t> &_deads;
        // int64_t _ms_last_update;
};

#endif /* !SYSTEMCOLLISION_HPP_ */
