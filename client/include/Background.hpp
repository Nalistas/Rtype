/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Background
*/

#include "Raylib/Sprite.hpp"

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_


/**
 * @brief Background class to handle the background and the parallax
 */
class Background {
    public:
        Background();
        Background(std::string const &path, std::size_t speed, std::size_t win_width, std::size_t win_height);
        ~Background();

        raylib::Sprite &getBackground();
        void setSpeed(std::size_t speed);
        void update(std::size_t timestamp);

    private:
        raylib::Sprite _background;
        std::size_t _speed;
        std::size_t _win_width;
        std::size_t _win_height;
};

#endif /* !BACKGROUND_HPP_ */
