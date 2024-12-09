/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemMusic
*/

#include "isystem.hpp"
#include "Raylib/RayMusic.hpp"

#ifndef SYSTEMMUSIC_HPP_
    #define SYSTEMMUSIC_HPP_

class SystemMusic : public ecs::isystem<raylib::RayMusic> {
    public:
        SystemMusic();
        ~SystemMusic();

    private:
        void operator()(ecs::registry &r, ecs::entity const &e, raylib::RayMusic &m) override;
};

#endif /* !SYSTEMMUSIC_HPP_ */
