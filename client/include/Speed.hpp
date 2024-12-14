/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Speed
*/

#include "raylib.h"

#ifndef SPEED_HPP_
#define SPEED_HPP_

class Speed {
    public:
        Speed();
        ~Speed();
        Vector2 getSpeed();
        void setSpeed(Vector2 speed);

    protected:
    private:
        Vector2 _speed;
};

#endif /* !SPEED_HPP_ */
