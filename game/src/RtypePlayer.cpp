#include "RtypePlayer.hpp"

RtypePlayer::RtypePlayer()
    : _position(0, 0), _speed(0, 0), _health(50)
{
}

RtypePlayer::~RtypePlayer()
{
}

const std::pair<std::size_t, std::size_t> &RtypePlayer::getPosition() const
{
    return _position;
}

void RtypePlayer::setPosition(std::size_t x, std::size_t y)
{
     _position = {x, y};
}


const std::pair<std::size_t, std::size_t> &RtypePlayer::getSpeed() const
{
    return _speed;
}

void RtypePlayer::setSpeed(std::size_t x, std::size_t y)
{
    _speed.first = x;
    _speed.second = y;
}

void RtypePlayer::setHealth(std::size_t health)
{
    _health = health;
}

size_t RtypePlayer::getHealth() const
{
    return _health;
}

graphics_interface::Sprite &RtypePlayer::getSprite()
{
    return _sprite;
}

void RtypePlayer::setSpritePath(std::string path)
{
    _sprite.path = path;
}
