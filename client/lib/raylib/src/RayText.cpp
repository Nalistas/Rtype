#include "RayText.hpp"
#include "raylib.h"

raylib::RayText::RayText(std::string text, int x, int y, int size, Color color)
    : _text(text), _x(x), _y(y), _size(size), _color(color)
{
}

raylib::RayText::~RayText()
{
}

void raylib::RayText::setText(std::string text)
{
    _text = text;
}

void raylib::RayText::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void raylib::RayText::setSize(int size)
{
    _size = size;
}

std::string const &raylib::RayText::getText() const
{
    return _text;
}

int raylib::RayText::getX() const
{
    return _x;
}

int raylib::RayText::getY() const
{
    return _y;
}

int raylib::RayText::getSize(void) const
{
    return _size;
}

void raylib::RayText::draw() const
{
    DrawText(_text.c_str(), _x, _y, _size, _color);
}
