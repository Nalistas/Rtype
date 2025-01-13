/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Background
*/

#include "Background.hpp"
#include <ctime>

#include <iostream>
#include "Raylib/TextureManager.hpp"

Background::Background() :
    _background(), _speed(0), _win_width(0), _win_height(0), _repeat(false), _move_type(BACKGROUND_MOVE_TYPE::NONE)
{
}

Background::~Background()
{
}

Background::Background(std::shared_ptr<raylib::TextureCpp> &path) :
    _background(path), _speed(0), _win_width(0), _win_height(0), _repeat(false), _move_type(BACKGROUND_MOVE_TYPE::NONE)
{
}

Background::Background(std::shared_ptr<raylib::TextureCpp> &path, std::size_t win_width, std::size_t win_height) :
    _background(path), _speed(0), _win_width(win_width), _win_height(win_height), _repeat(false), _move_type(BACKGROUND_MOVE_TYPE::NONE)
{
    _background.set_position(static_cast<float>(_win_width) / 2, static_cast<float>(_win_height) / 2);
}

Background::Background(std::shared_ptr<raylib::TextureCpp> &path, std::size_t win_width, std::size_t win_height, double speed) :
    _background(path), _speed(speed), _win_width(win_width), _win_height(win_height), _repeat(false), _move_type(BACKGROUND_MOVE_TYPE::NONE)
{
}

void Background::setComponent(graphics_interface::Background const &background)
{
    auto texture = raylib::TextureManager::getTexture(background.path);
    _background.set_texture(texture);
    _speed = static_cast<int>(background.speed);
    if (background.direction == graphics_interface::BackgroundDirection::X) {
        this->setMoveType(BACKGROUND_MOVE_TYPE::MOVE_X);
    }
    if (background.direction == graphics_interface::BackgroundDirection::Y) {
        this->setMoveType(BACKGROUND_MOVE_TYPE::MOVE_Y);
    }
    _repeat = background.repeat;
}

void Background::setSpeed(double speed)
{
    _speed = speed;
}

double Background::getSpeed(void) const
{
    return _speed;
}

void Background::setWindowDimensions(std::size_t win_width, std::size_t win_height)
{
    _win_width = win_width;
    _win_height = win_height;
    _background.set_position(static_cast<float>(_win_width) / 2, static_cast<float>(_win_height) / 2);
}

void Background::set_texture(std::shared_ptr<raylib::TextureCpp> &path)
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

void Background::draw()
{
    // Position actuelle du background
    float x = _background.get_position().x;
    float y = _background.get_position().y;
    float bgWidth = _background.get_size().x;
    float bgHeight = _background.get_size().y;

    float saved_x = x;
    float saved_y = y;

    _background.draw();

    if (!_repeat) {
        return;
    }

    if (this->_move_type == Background::PARALLAX || this->_move_type == Background::PARALLAX_X || this->_move_type == Background::MOVE_X) {
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
    
    if (this->_move_type == Background::PARALLAX || this->_move_type == Background::PARALLAX_Y || this->_move_type == Background::MOVE_Y) {
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
    raylib::Vector2 pos = _background.get_position();
    raylib::Vector2 size = _background.get_size();
    float speed_x = _speed * (_move_type == Background::BACKGROUND_MOVE_TYPE::MOVE_X ? 1 : 0);
    float speed_y = _speed * (_move_type == Background::BACKGROUND_MOVE_TYPE::MOVE_Y ? 1 : 0);

    _background.set_position(pos.x - speed_x * timestamp, pos.y - speed_y * timestamp);

    pos = _background.get_position();

    if (!_repeat) {
        return;
    }

    if (_move_type == Background::MOVE_X) {
        while (_background.get_position().x <= -_background.get_size().x) {
            _background.set_position(_background.get_position().x + size.x, pos.y);
        } 
        while (_background.get_position().x >= _win_width) {
            _background.set_position(_background.get_position().x - size.x, pos.y);
        }
    }
    pos = _background.get_position();
    if (_move_type == Background::MOVE_Y) {
        if (_background.get_position().y <= -_background.get_size().y) {
            _background.set_position(pos.x, _background.get_position().y + size.y);
        } else if (_background.get_position().y >= _win_height) {
            _background.set_position(pos.x, _background.get_position().y - size.y);
        }
    }
}

void Background::setParallax(void)
{
    raylib::Vector2 size = _background.get_size();
    raylib::Vector2 pos = {0, 0};

    if (!this->_get_parallax_pos) {
        return;
    }
    raylib::Vector2 ref = this->_get_parallax_pos();
    float x_ref = ref.x - size.x / 2;
    float y_ref = ref.y - size.y / 2;

    if (_speed == 0) {
        return;
    }
    if (this->_move_type == Background::PARALLAX || this->_move_type == Background::PARALLAX_X) {
        pos.x = (x_ref) * _speed / 10;
    }
    if (this->_move_type == Background::PARALLAX || this->_move_type == Background::PARALLAX_Y) {
        pos.y = (y_ref) * _speed / 10;
    }

    _background.set_position(pos.x + size.x / 2, pos.y + size.y / 2);
}

void Background::loop(bool value)
{
    _repeat = value;
}

void Background::setMoveType(Background::BACKGROUND_MOVE_TYPE type)
{
    _move_type = type;
}

void Background::update_position(std::time_t timestamp)
{
    if (this->_speed == 0 || this->_move_type == Background::BACKGROUND_MOVE_TYPE::NONE) {
        return;
    }

    if (this->_move_type == Background::MOVE_X || this->_move_type == Background::MOVE_Y) {
        this->move(timestamp);
    }

    if (this->_move_type == Background::PARALLAX || this->_move_type == Background::PARALLAX_X || this->_move_type == Background::PARALLAX_Y) {
        this->setParallax();
    }
}

void Background::setParallaxPos(std::function<raylib::Vector2(void)> const &get_parallax_pos)
{
    this->_get_parallax_pos = get_parallax_pos;
}
