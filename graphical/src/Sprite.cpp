/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Sprite
*/

#include "Sprite.hpp"
#include <stdexcept>

raylib::Sprite::Sprite(std::string const &texture_path) :
    _rotation(0), _frame_count(0), _offset({0, 0}), _current_frame(0)
{
    _texture = LoadTexture(texture_path.c_str());
    if (_texture.id == 0) {
        throw std::runtime_error("Failed to load texture: " + texture_path);
    }

    _source_rect = {0, 0, static_cast<float>(_texture.width), static_cast<float>(_texture.height)};
    _source_rect_origin = _source_rect;
    _destination_rect = {0, 0, static_cast<float>(_texture.width), static_cast<float>(_texture.height)};
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

raylib::Sprite::Sprite(std::string const &texture_path, Rectangle texture_rect, Rectangle on_window_rect)
    : _source_rect(texture_rect), _destination_rect(on_window_rect), _rotation(0), _source_rect_origin(texture_rect),
      _frame_count(0), _offset({0, 0}), _current_frame(0)
{
    _texture = LoadTexture(texture_path.c_str());
    if (_texture.id == 0) {
        throw std::runtime_error("Failed to load texture: " + texture_path);
    }
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
{
    UnloadTexture(_texture);
}

void raylib::Sprite::draw()
{
    DrawTexturePro(_texture, _source_rect, _destination_rect, _center, _rotation, WHITE);
}

void raylib::Sprite::set_texture(std::string const &texture_path)
{
    UnloadTexture(_texture);
    _texture = LoadTexture(texture_path.c_str());
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

Vector2 raylib::Sprite::get_position() const
{
    return {_destination_rect.x, _destination_rect.y};
}

Vector2 raylib::Sprite::get_size() const
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

Vector2 raylib::Sprite::get_offset() const
{
    return _offset;
}

void raylib::Sprite::set_offset(Vector2 offset)
{
    _offset = offset;
}

void raylib::Sprite::set_offset(float x, float y)
{
    _offset.x = x;
    _offset.y = y;
}

unsigned int raylib::Sprite::get_frame_count() const
{
    return _frame_count;
}

void raylib::Sprite::set_frame_count(unsigned int frame_count)
{
    _frame_count = frame_count;
}

void raylib::Sprite::set_current_frame(unsigned int current_frame)
{
    _current_frame = current_frame;
}

unsigned int raylib::Sprite::get_current_frame() const
{
    return _current_frame;
}

void raylib::Sprite::next_frame()
{
    _source_rect.x += _offset.x;
    _source_rect.y += _offset.y;

    _current_frame++;
    if (_current_frame >= _frame_count) {
        _source_rect.x = _source_rect_origin.x;
        _source_rect.y = _source_rect_origin.y;
        _current_frame = 0;
    }
}
