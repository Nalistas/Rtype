/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** RtypeEnemie
*/

#include <utility>
#include <cstddef>

#ifndef RTYPEENEMY_HPP_
    #define RTYPEENEMY_HPP_

class RtypeEnemy {
    public:
        RtypeEnemy();
        ~RtypeEnemy();

        const std::pair<std::size_t, std::size_t> &getPosition(void) const;

        void setPosition(std::size_t x, std::size_t y);


        const std::pair<std::size_t, std::size_t> &getSpeed(void) const;

        void setSpeed(std::size_t x, std::size_t y);

        void setHealth(std::size_t health);

        size_t getHealth(void) const;

    private:
        std::pair<std::size_t, std::size_t> _position;
        std::pair<std::size_t, std::size_t> _speed;
        size_t _health;
};

#endif /* !RTYPEENEMY_HPP_ */