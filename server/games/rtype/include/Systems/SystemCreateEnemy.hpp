/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCreateEnemy
*/

#include "isystem.hpp"
#include "IGame.hpp"
#include "Component/Position.hpp"


#ifndef SYSTEMCREATEENEMY_HPP_
#define SYSTEMCREATEENEMY_HPP_

class SystemCreateEnemy : public ecs::isystem<> {
    public:
        SystemCreateEnemy(rtype::IGame::Creater creater);
        ~SystemCreateEnemy();

        void operator()(ecs::registry &registry);

    protected:
    private:
        int64_t _ms_last_update;
        rtype::IGame::Creater _creater;
};

#endif /* !SYSTEMCREATEENEMY_HPP_ */
