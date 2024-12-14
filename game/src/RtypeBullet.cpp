/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** RtypeBullet
*/

#include "RtypeBullet.hpp"

RtypeBullet::RtypeBullet(std::size_t x, std::size_t y, std::size_t speedX, std::size_t speedY)
    : _position(x, y), _speed(speedX, speedY)
{
}

RtypeBullet::~RtypeBullet() {}

const std::pair<std::size_t, std::size_t>& RtypeBullet::getPosition(void) const {
    return _position;
}

void RtypeBullet::setPosition(std::size_t x, std::size_t y) {
    _position = std::make_pair(x, y);
}

void RtypeBullet::updatePosition() {
    _position.first += _speed.first;
    _position.second += _speed.second;
}

const std::pair<std::size_t, std::size_t>& RtypeBullet::getSpeed(void) const {
    return _speed;
}

void RtypeBullet::setSpeed(std::size_t speedX, std::size_t speedY) {
    _speed = std::make_pair(speedX, speedY);
}
