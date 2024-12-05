/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemBackground
*/

#include "isystem.hpp"
#include "Background.hpp"

#ifndef SYSTEMBACKGROUND_HPP_
    #define SYSTEMBACKGROUND_HPP_

class SystemBackground : public ecs::isystem<Background> {
    public:
        SystemBackground(std::size_t const &elpased_time);
        ~SystemBackground();

        void operator()(ecs::iregistry &r, Background &b) override;

    private:
        std::size_t const &_elpased_time;
};

#endif /* !SYSTEMBACKGROUND_HPP_ */
