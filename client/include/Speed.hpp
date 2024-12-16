/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Speed
*/


#ifndef SPEED_HPP_
    #define SPEED_HPP_

namespace raylib {
    #include "raylib.h"
}

class Speed {
    public:
        Speed();
        ~Speed();
        raylib::Vector2 getSpeed();
        void setSpeed(raylib::Vector2 speed);

    protected:
    private:
        raylib::Vector2 _speed;
};

#endif /* !SPEED_HPP_ */
