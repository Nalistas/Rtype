/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAnimation
*/

#include "Animation.hpp"
#include "Raylib/Sprite.hpp"
#include "isystem.hpp"

#ifndef SYSTEMANIMATION_HPP_
    #define SYSTEMANIMATION_HPP_

class SystemAnimation : public ecs::isystem<Animation, raylib::Sprite> {
    public:
        SystemAnimation(std::size_t const &elpased_time);
        ~SystemAnimation();
        void operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Animation &animation, raylib::Sprite &sprite);

    protected:
    private:
        std::size_t const &_elpased_time;
};

#endif /* !SYSTEMANIMATION_HPP_ */
