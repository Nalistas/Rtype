/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

/**
 * @brief Position component
 */
struct Position {
    Position(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

/**
 * @brief Speed component
 */
struct Speed {
    Speed(int x, int y) : x(x), y(y) {}
    char x;
    char y;
};

/**
 * @brief Size component
 */
struct Hitbox {
    Hitbox(int width, int height) : width(width), height(height) {}
    int width;
    int height;
};

/**
 * @brief Life component
 */
struct Life {
    Life(int life) : life(life) {}
    int life;
};

/**
 * @brief Damage component
 */
struct Damage {
    Damage(int damage) : damage(damage) {}
    int damage;
};

/**
 * @brief enum for the side of the entity
 */
enum SIDE {
    PLAYER,
    ENEMY
};

#endif /* !POSITION_HPP_ */
