/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** RtypeBullet
*/

#ifndef RTYPEBULLET_HPP_
#define RTYPEBULLET_HPP_

#include <utility>
#include <cstddef>

class RtypeBullet {
    public:
        RtypeBullet(std::size_t x, std::size_t y, std::size_t speedX, std::size_t speedY);
        ~RtypeBullet();

        const std::pair<std::size_t, std::size_t>& getPosition(void) const;
        void setPosition(std::size_t x, std::size_t y);

        void updatePosition();

        const std::pair<std::size_t, std::size_t>& getSpeed(void) const;
        void setSpeed(std::size_t x, std::size_t y);

    private:
        std::pair<std::size_t, std::size_t> _position;
        std::pair<std::size_t, std::size_t> _speed;
};

#endif /* !RTYPEBULLET_HPP_ */
