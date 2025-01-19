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
        SystemCollision(rtype::IGame::Deleter deleter);
        ~SystemCollision();

        void operator()(ecs::registry &registry, sparse_array<Position> &position, sparse_array<Hitbox> &hitbox, sparse_array<Damage> &damage, sparse_array<Life> &health, sparse_array<SIDE> &side);
        bool checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB);

    protected:
    private:
        rtype::IGame::Deleter _deleter;
};

#endif /* !SYSTEMCOLLISION_HPP_ */
