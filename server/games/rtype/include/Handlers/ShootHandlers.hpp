/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** ShootHandlers
*/

#include "IGame.hpp"
#include "registry.hpp"
#include <unordered_set>

#ifndef SHOOTHANDLERS_HPP_
    #define SHOOTHANDLERS_HPP_
/**
 * @brief ShootHandlers class to handle the shoot action
 */
class ShootHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new ShootHandlers object
         * 
         * @param reg
         * @param creater
         * @param players
         */
        ShootHandlers(const std::shared_ptr<ecs::registry> &reg, rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players, std::unordered_set<std::size_t> const &_deads);
        ~ShootHandlers();

        /**
         * @brief ShootHandlers
         * 
         * @param client 
         * @param mouse_x 
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    private:
        std::shared_ptr<ecs::registry> _registry;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
        std::unordered_set<std::size_t> const &_deads;
        std::unordered_map<std::size_t, std::size_t> _players_shoot;
};


#endif /* !SHOOTHANDLERS_HPP_ */
