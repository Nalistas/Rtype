/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCreateEnemy
*/

#include "isystem.hpp"
#include "IGame.hpp"
#include "Component/Position.hpp"
#include <unordered_map>

#ifndef SYSTEMCREATEENEMY_HPP_
#define SYSTEMCREATEENEMY_HPP_

class SystemCreateEnemy : public ecs::isystem<> {
    public:
        SystemCreateEnemy(rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players);
        ~SystemCreateEnemy();

        void operator()(ecs::registry &registry);

    protected:
    private:
        int64_t _ms_last_update;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
};

#endif /* !SYSTEMCREATEENEMY_HPP_ */
