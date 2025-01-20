/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "isystem.hpp"
#include "Component/Position.hpp"
#include "IGame.hpp"

#ifndef SYSTEMCOLLISION_HPP_
#define SYSTEMCOLLISION_HPP_

class SystemCollision : public ecs::isystem<Position, Hitbox, Damage, Life, SIDE> {
    public:
        SystemCollision(rtype::IGame::Deleter const &deleter, std::unordered_map<std::size_t, std::size_t> &players);
        ~SystemCollision();

        void operator()(ecs::registry &registry, sparse_array<Position> &position, sparse_array<Hitbox> &hitbox, sparse_array<Damage> &damage, sparse_array<Life> &health, sparse_array<SIDE> &side);
        bool checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB);

    private:
        void broadcast(std::size_t entity_deleted, ecs::registry &registry);

        rtype::IGame::Deleter const &_deleter;
        std::unordered_map<std::size_t, std::size_t> &_players;
};

#endif /* !SYSTEMCOLLISION_HPP_ */
