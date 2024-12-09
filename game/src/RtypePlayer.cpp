#include "RtypePlayer.hpp"

RtypePlayer::RtypePlayer()
    : _position(0, 0), _speed(0, 0)
{
}

RtypePlayer::~RtypePlayer()
{
}

// Retourne une référence constante à la position
const std::pair<std::size_t, std::size_t> &RtypePlayer::getPosition() const
{
    return _position;
}

// Modifie la position
void RtypePlayer::setPosition(std::size_t x, std::size_t y)
{
    _position.first = x;
    _position.second = y;
}


const std::pair<std::size_t, std::size_t> &RtypePlayer::getSpeed() const
{
    return _speed;
}

// Modifie la position
void RtypePlayer::setSpeed(std::size_t x, std::size_t y)
{
    _speed.first = x;
    _speed.second = y;
}
