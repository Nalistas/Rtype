/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "IGame.hpp"

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class Rtype : public rtype::IGame {
    public:
        Rtype();
        ~Rtype();

        std::string getName(void) override;

        void setRegistry(ecs::registry &reg) override;

        void processClientAction(ecs::registry &reg, std::string const &action, std::size_t client) override;
};

#endif /* !RTYPE_HPP_ */
