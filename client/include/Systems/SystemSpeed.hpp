/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemSpeed
*/

#include "isystem.hpp"


#ifndef SYSTEMSPEED_HPP_
#define SYSTEMSPEED_HPP_

class SystemSpeed {
    public:
        SystemSpeed();
        ~SystemSpeed();
        void operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, Sprite &sprite)


    protected:
    private:
};

#endif /* !SYSTEMSPEED_HPP_ */
