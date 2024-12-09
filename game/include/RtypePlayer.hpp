/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** RtypePlayer
*/

#include <utility>
#include <cstddef>

#ifndef RTYPEPLAYER_HPP_
    #define RTYPEPLAYER_HPP_

class RtypePlayer {
    public:
        RtypePlayer();
        ~RtypePlayer();

        const std::pair<std::size_t, std::size_t> &getPosition(void) const;

        void setPosition(std::size_t x, std::size_t y);


        const std::pair<std::size_t, std::size_t> &getSpeed(void) const;

        void setSpeed(std::size_t x, std::size_t y);

    private:
        std::pair<std::size_t, std::size_t> _position; // Stocke la position du joueur
        std::pair<std::size_t, std::size_t> _speed; // Stocke la position du joueur
};

#endif /* !RTYPEPLAYER_HPP_ */
