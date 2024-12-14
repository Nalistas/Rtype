/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Sprite
*/

#include "Raylib/Sprite.hpp"
#include <stdexcept>

raylib::Sprite::Sprite() : _rotation(0), _frame_count(0), _current_frame(0), _offset({0, 0}) {}

raylib::Sprite::Sprite(std::string const &texture_path) :
    _rotation(0), _frame_count(0), _current_frame(0), _offset({0, 0})
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
    : _destination_rect(on_window_rect), _rotation(0), _source_rect(texture_rect), _source_rect_origin(texture_rect),
      _frame_count(0), _current_frame(0), _offset({0, 0})
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

#include <iostream>

void raylib::Sprite::draw()
{
    if (_texture.id == 0) {
        // std::cout << "Texture not loaded" << std::endl;
        return;
    }
    DrawTexturePro(_texture, _source_rect, _destination_rect, _center, _rotation, WHITE);
}

void raylib::Sprite::set_texture(std::string const &texture_path)
{
    UnloadTexture(_texture);
    _texture = LoadTexture(texture_path.c_str());
    if (_texture.id == 0) {
        throw std::runtime_error("Failed to load texture: " + texture_path);
    }
    _source_rect = {0, 0, static_cast<float>(_texture.width), static_cast<float>(_texture.height)};
    _source_rect_origin = _source_rect;
    _destination_rect = {_destination_rect.x, _destination_rect.y, static_cast<float>(_texture.width), static_cast<float>(_texture.height)};
    _center = {_destination_rect.width / 2, _destination_rect.height / 2};
}

void raylib::Sprite::setComponent(rtype_protocol::Sprite const &sprite)
{
    _texture = LoadTexture(sprite.path.c_str());
    if (_texture.id == 0) {
        throw std::runtime_error("Failed to load texture: " + sprite.path);
    }
    float offset_x = static_cast<float>(sprite.offset_x);
    float offset_y = static_cast<float>(sprite.offset_y);
    float src_rect_width = sprite.text_rect_width == 0 ? static_cast<float>(_texture.width) : static_cast<float>(sprite.text_rect_width);
    float src_rect_height = sprite.text_rect_height == 0 ? static_cast<float>(_texture.height) : static_cast<float>(sprite.text_rect_height);
    float destination_rect_x = static_cast<float>(sprite.pos_x);
    float destination_rect_y = static_cast<float>(sprite.pos_y);
    float size_x = static_cast<float>(sprite.size_x);
    float size_y = static_cast<float>(sprite.size_y);

    std::cout << "offset_x: " << offset_x << std::endl;
    std::cout << "offset_y: " << offset_y << std::endl;
    std::cout << "src_rect_width: " << src_rect_width << std::endl;
    std::cout << "src_rect_height: " << src_rect_height << std::endl;
    std::cout << "destination_rect_x: " << destination_rect_x << std::endl;
    std::cout << "destination_rect_y: " << destination_rect_y << std::endl;
    std::cout << "size_x: " << size_x << std::endl;

    this->resize_x(size_x);
    this->resize_y(size_y);
    this->set_position(destination_rect_x, destination_rect_y);
    this->set_source_rect({offset_x, offset_y, src_rect_width, src_rect_height});
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
        float aspect_ratio = static_cast<float>(_texture.height) / static_cast<float>(_texture.width);
        float scale_y = scale_x * aspect_ratio;
        set_size(scale_x, scale_y);
    } else {
        set_size(scale_x, this->_destination_rect.height);
    }
}

void raylib::Sprite::resize_y(float scale_y, bool preserve_aspect_ratio)
{
    if (preserve_aspect_ratio) {
        float aspect_ratio = static_cast<float>(_texture.width) / static_cast<float>(_texture.height);
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
