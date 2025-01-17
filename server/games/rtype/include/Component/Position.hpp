/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

struct Position {
    Position(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

struct Velocity {
    Velocity(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

struct Hitbox {
    Hitbox(int width, int height) : width(width), height(height) {}
    int width;
    int height;
};

struct Life {
    Life(int life) : life(life) {}
    int life;
};

enum SIDE {
    PLAYER,
    ENEMY
};

#endif /* !POSITION_HPP_ */
