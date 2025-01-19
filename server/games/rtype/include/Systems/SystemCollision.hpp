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

class SystemCollision : public ecs::isystem<Position, Hitbox, Damage> {
    public:
        SystemCollision(rtype::IGame::Deleter creater);
        ~SystemCollision();

        void operator()(ecs::registry &registry, Position &position, Hitbox &hitbox, Damage &damage);

    protected:
    private:
        int64_t _ms_last_update;
        rtype::IGame::Deleter _deleter;
};

#endif /* !SYSTEMCOLLISION_HPP_ */
