/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAnimation
*/

#include "Animation.hpp"
#include "Sprite.hpp"

#ifndef SYSTEMANIMATION_HPP_
#define SYSTEMANIMATION_HPP_

class SystemAnimation {
    public:
        SystemAnimation(std::size_t const &elpased_time);
        ~SystemAnimation();
        void operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Animation &animation, Sprite &sprite);

    protected:
    private:
        std::size_t const &_elpased_time;
};

#endif /* !SYSTEMANIMATION_HPP_ */
