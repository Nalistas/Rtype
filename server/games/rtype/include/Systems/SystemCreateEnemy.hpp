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

/**
 * @brief SystemCreateEnemy class to handle the creation of the enemies
 */
class SystemCreateEnemy : public ecs::isystem<> {
    public:
        /**
         * @brief Construct a new SystemCreateEnemy object
         * 
         * @param creater
         * @param players
         */
        SystemCreateEnemy(rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players);
        ~SystemCreateEnemy();

        /**
         * @brief Update the speed and position of the player
         * 
         * @param registry
         */
        void operator()(ecs::registry &registry);

        /**
         * @brief Create the enemy 1
         * 
         * @param registry
         */
        void createEnemy1(ecs::registry &registry);

        /**
         * @brief Create the enemy 2
         * 
         * @param registry
         */
        void createEnemy2(ecs::registry &registry);

    protected:
    private:
        int64_t _ms_last_update;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
        int _nb_enemies;
};

#endif /* !SYSTEMCREATEENEMY_HPP_ */
