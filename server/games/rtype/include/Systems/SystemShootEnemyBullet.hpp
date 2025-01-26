/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemShootEnemy
*/

#include "isystem.hpp"
#include "IGame.hpp"
#include "Component/Position.hpp"
#include <unordered_map>

#ifndef SYSTEMSHOOTENEMYBULLET_HPP_
    #define SYSTEMSHOOTENEMYBULLET_HPP_


class SystemShootEnemyBullet : public ecs::isystem<Position, Type, SIDE>{ 
    public:
        SystemShootEnemyBullet(rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players);
        ~SystemShootEnemyBullet();

        void operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Type> &types, sparse_array<SIDE> &sides);



    protected:
    private:
        int64_t _ms_last_update;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
};

#endif /* !SYSTEMSHOOTENEMYBULLET_HPP_ */
