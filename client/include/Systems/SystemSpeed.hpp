/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemSpeed
*/

#include "isystem.hpp"
#include "Speed.hpp"
#include "Sprite.hpp"


#ifndef SYSTEMSPEED_HPP_
#define SYSTEMSPEED_HPP_

class SystemSpeed {
    public:
         /**
         * @brief Construct a new System Speed object
         * @param elpased_time the reference to the elpased time
         */
        SystemSpeed(std::size_t const &elpased_time);
        ~SystemSpeed();
        void operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, Sprite &sprite);


    protected:
    private:
        std::size_t const &_elpased_time;
};

#endif /* !SYSTEMSPEED_HPP_ */
