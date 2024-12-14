/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Animation
*/

#include "Animation.hpp"

Animation::Animation()
{}

Animation::~Animation()
{
}

void Animation::setFrame(int frame)
{
    _current_frame = frame;
}

void Animation::setMaxFrame(int max_frame)
{
    _max_frame = max_frame;
}

void Animation::setMsPerFrame(int ms_per_frame)
{
    _ms_per_frame = ms_per_frame;
}

void Animation::setSourceRect(raylib::Rectangle const &source_rect)
{
    _source_rect = source_rect;
}

void Animation::update()
{
    if (GetTime() > _ms_per_frame) {
        _current_frame++;
        if (_current_frame >= _max_frame)
            _current_frame = 0;
        _source_rect.x = _source_rect.width * _current_frame;
        SetTime(0);
    }
}

raylib::Rectangle Animation::getSourceRect() const
{
    return _source_rect;
}

int Animation::getFrame() const
{
    return _current_frame;
}

int Animation::getMaxFrame() const
{
    return _max_frame;
}

int Animation::getMsPerFrame() const
{
    return _ms_per_frame;
}
