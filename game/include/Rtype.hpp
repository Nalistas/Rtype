/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "IGame.hpp"
#include <vector>

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class Rtype : public rtype::IGame {
    public:
        Rtype();
        ~Rtype();

        std::string getName(void) override;

        void setRegistry(ecs::registry &reg) override;

        void setBroadcastCreate(std::function<void(ecs::entity const &e)>) override;
        void setBroadcastDelete(std::function<void(ecs::entity const &e)>) override;
        void setBroadcastUpdate(std::function<void(ecs::entity const &e)>) override;

        std::vector<rtype::ClientAction> getClientActionHandlers(void) override;

};

#endif /* !RTYPE_HPP_ */
