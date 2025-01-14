/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Sprite
*/

#include "Sprite.hpp"
#include <stdexcept>
#include "TextureManager.hpp"

raylib::Sprite::Sprite() : _rotation(0), _frame_count(0), _current_frame(0), _offset({0, 0})
{}

raylib::Sprite::Sprite(std::shared_ptr<raylib::TextureCpp> &text) :
    _rotation(0), _frame_count(0), _current_frame(0), _offset({0, 0})
{
    _texture = text;

    _source_rect = {0, 0, static_cast<float>(_texture->get_texture().width), static_cast<float>(_texture->get_texture().height)};
    _source_rect_origin = _source_rect;
    _destination_rect = {0, 0, static_cast<float>(_texture->get_texture().width), static_cast<float>(_texture->get_texture().height)};
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

raylib::Sprite::Sprite(std::shared_ptr<raylib::TextureCpp> &text, Rectangle texture_rect, Rectangle on_window_rect)
    : _destination_rect(on_window_rect), _rotation(0), _source_rect(texture_rect), _source_rect_origin(texture_rect),
      _frame_count(0), _current_frame(0), _offset({0, 0})
{
    _texture = text;
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

void raylib::Sprite::set_position(float x, float y)
{
    _destination_rect.x = x;
    _destination_rect.y = y;
}

void raylib::Sprite::set_size(float x, float y)
{
    _destination_rect.width = x;
    _destination_rect.height = y;

    _center.x = x / 2;
    _center.y = y / 2;
}

raylib::Sprite::~Sprite()
{}

#include <iostream>

void raylib::Sprite::draw()
{
    if (_texture->get_texture().id == 0) {
        return;
    }
    DrawTexturePro(_texture->get_texture(), _source_rect, _destination_rect, _center, _rotation, WHITE);
}

void raylib::Sprite::set_texture(std::shared_ptr<raylib::TextureCpp> &text)
{
    _texture.reset();
    _texture = text;
    _source_rect = {0, 0, static_cast<float>(_texture->get_texture().width), static_cast<float>(_texture->get_texture().height)};
    _source_rect_origin = _source_rect;
    _destination_rect = {_destination_rect.x, _destination_rect.y, static_cast<float>(_texture->get_texture().width), static_cast<float>(_texture->get_texture().height)};
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

void raylib::Sprite::set_source_rect(Rectangle texture_rect)
{
    _source_rect = texture_rect;
    _source_rect_origin = texture_rect;
}

void raylib::Sprite::set_destination_rect(Rectangle on_window_rect)
{
    _destination_rect = on_window_rect;
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

raylib::Vector2 raylib::Sprite::get_position() const
{
    return {_destination_rect.x, _destination_rect.y};
}

raylib::Vector2 raylib::Sprite::get_size() const
{
    return {_destination_rect.width, _destination_rect.height};
}

void raylib::Sprite::set_rotation(float rotation)
{
    _rotation = rotation;
}

float raylib::Sprite::get_rotation() const
{
    return _rotation;
}

void raylib::Sprite::resize_x(float scale_x, bool preserve_aspect_ratio)
{
    if (preserve_aspect_ratio) {
        float aspect_ratio = static_cast<float>(_texture->get_texture().height) / static_cast<float>(_texture->get_texture().width);
        float scale_y = scale_x * aspect_ratio;
        set_size(scale_x, scale_y);
    } else {
        set_size(scale_x, this->_destination_rect.height);
    }
}

void raylib::Sprite::resize_y(float scale_y, bool preserve_aspect_ratio)
{
    if (preserve_aspect_ratio) {
        float aspect_ratio = static_cast<float>(_texture->get_texture().width) / static_cast<float>(_texture->get_texture().height);
        float scale_x = scale_y * aspect_ratio;
        set_size(scale_x, scale_y);
    } else {
        set_size(this->_destination_rect.width, scale_y);
    }
}

void raylib::Sprite::set_offset(float x, float y)
{
    _offset = {x, y};
}
