/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Background
*/

#include "Background.hpp"

Background::Background() :
    _background(), _speed_x(0), _speed_y(0), _win_width(0), _win_height(0), _repeat_x(false), _repeat_y(false)
{
}

Background::~Background()
{
}

Background::Background(std::string const &path, std::size_t win_width, std::size_t win_height) :
    _background(path), _speed_x(0), _speed_y(0), _win_width(win_width), _win_height(win_height), _repeat_x(false), _repeat_y(false)
{
    _background.set_position(static_cast<float>(_win_width) / 2, static_cast<float>(_win_height) / 2);
}

Background::Background(std::string const &path, std::size_t win_width, std::size_t win_height, double speedX, double speedY) :
    _background(path), _speed_x(speedX), _speed_y(speedY), _win_width(win_width), _win_height(win_height), _repeat_x(false), _repeat_y(false)
{
}

void Background::setSpeedX(double speedX)
{
    _speed_x = speedX;
}

void Background::setSpeedY(double speedY)
{
    _speed_y = speedY;
}

double Background::getSpeedX(void) const
{
    return _speed_x;
}

double Background::getSpeedY(void) const
{
    return _speed_y;
}

void Background::setWindowDimensions(std::size_t win_width, std::size_t win_height)
{
    _win_width = win_width;
    _win_height = win_height;
    _background.set_position(static_cast<float>(_win_width) / 2, static_cast<float>(_win_height) / 2);
}

void Background::setTexture(std::string const &path)
{
    _background.set_texture(path);
}

void Background::resize_x(float scale_x, bool preserve_aspect_ratio)
{
    _background.resize_x(scale_x, preserve_aspect_ratio);
}

void Background::resize_y(float scale_y, bool preserve_aspect_ratio)
{
    _background.resize_y(scale_y, preserve_aspect_ratio);
}

void Background::auto_resize_x(void)
{
    _background.resize_x(static_cast<float>(_win_width), true);
}

void Background::auto_resize_y(void)
{
    _background.resize_y(static_cast<float>(_win_height), true);
}

#include <iostream>

void Background::draw() {
    // Position actuelle du background
    float x = _background.get_position().x;
    float y = _background.get_position().y;
    float bgWidth = _background.get_size().x;
    float bgHeight = _background.get_size().y;

    float saved_x = x;
    float saved_y = y;

    _background.draw();

    if (_repeat_x) { 
        float drawX = x;
        while (drawX < _win_width) {
            drawX += bgWidth;
            _background.set_position(drawX, y);
            _background.draw();
        }
        drawX = x;
        while (drawX > -bgWidth) {
            drawX -= bgWidth;
            _background.set_position(drawX, y);
            _background.draw();
        }
    }
    
    if (_repeat_y) {
        float drawY = y;
        while (drawY < _win_height) {
            drawY += bgHeight;
            _background.set_position(x, drawY);
            _background.draw();
        }
        drawY = y;
        while (drawY > -bgHeight) {
            drawY -= bgHeight;
            _background.set_position(x, drawY);
            _background.draw();
        }
    }
    _background.set_position(saved_x, saved_y);
}



void Background::move(std::size_t timestamp)
{
    Vector2 pos = _background.get_position();
    Vector2 size = _background.get_size();

    _background.set_position(pos.x - _speed_x * timestamp, pos.y - _speed_y * timestamp);
    pos = _background.get_position();
    if (_repeat_x) {
        while (_background.get_position().x <= -_background.get_size().x) {
            _background.set_position(_background.get_position().x + size.x, pos.y);
        } 
        while (_background.get_position().x >= _win_width) {
            _background.set_position(_background.get_position().x - size.x, pos.y);
        }
    }
    pos = _background.get_position();
    if (_repeat_y) {
        if (_background.get_position().y <= -_background.get_size().y) {
            _background.set_position(pos.x, _background.get_position().y + size.y);
        } else if (_background.get_position().y >= _win_height) {
            _background.set_position(pos.x, _background.get_position().y - size.y);
        }
    }
}

void Background::setParallax(std::size_t x_ref, std::size_t y_ref)
{
    Vector2 size = _background.get_size();
    Vector2 pos = _background.get_position();

    if (_speed_x == 0 && _speed_y == 0) {
        return;
    }
    if (_speed_x != 0) {
        pos.x = (x_ref - size.x / 2) * _speed_x / 10;
    }
    if (_speed_y != 0) {
        pos.y = (y_ref - size.y / 2) * _speed_y / 10;
    }

    _background.set_position(pos.x, pos.y);
}

void Background::loop_x(bool value)
{
    _repeat_x = value;
}

void Background::loop_y(bool value)
{
    _repeat_y = value;
}
