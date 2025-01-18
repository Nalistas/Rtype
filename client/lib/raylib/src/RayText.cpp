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

bool raylib::RayText::operator==(const raylib::RayText &other) const
{
    return _text == other._text && _x == other._x && _y == other._y && _size == other._size && _color.r == other._color.r && _color.g == other._color.g && _color.b == other._color.b && _color.a == other._color.a;
}

bool raylib::RayText::operator!=(const raylib::RayText &other) const
{
    return !(*this == other);
}

bool raylib::RayText::operator<(const raylib::RayText &other) const
{
    if (_text != other._text)
        return _text < other._text;
    if (_x != other._x)
        return _x < other._x;
    if (_y != other._y)
        return _y < other._y;
    if (_size != other._size)
        return _size < other._size;
    if (_color.r != other._color.r)
        return _color.r < other._color.r;
    if (_color.g != other._color.g)
        return _color.g < other._color.g;
    if (_color.b != other._color.b)
        return _color.b < other._color.b;
    return _color.a < other._color.a;
}

bool raylib::RayText::operator>(const raylib::RayText &other) const
{
    return other < *this;
}
