/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GraphicsManager
*/

#include "GraphicsManager.hpp"
#include <limits>
#include <iostream>

GraphicsManager::GraphicsManager(raylib::Window &window) :
    _mustClear(false), _window(window)
{
    std::cout << "must clear ? " << _mustClear << std::endl;
    _last_frame_time = std::chrono::high_resolution_clock::now();
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::changeScene(std::function<void()> const &callback)
{
    _mustClear = true;
    next_scene = callback;
}

void GraphicsManager::_clearElements()
{
    _sprites.clear();
    _musics.clear();
    _texts.clear();
    _backgrounds.clear();

    _spriteClickCallbacks.clear();
    _textClickCallbacks.clear();
    _is_keyboard_binded_to_text = false;
    _mustClear = false;
    next_scene();
}

void GraphicsManager::display()
{
    if (_window.is_mouse_button(raylib::Window::PRESSED, 0)) {
        int x = _window.get_mouse_position().x;
        int y = _window.get_mouse_position().y;
        for (auto &sprite : _sprites) {
            int top_left_x = sprite.second.get_position().x - sprite.second.get_size().x / 2;
            int top_left_y = sprite.second.get_position().y - sprite.second.get_size().y / 2;
            int bottom_right_x = sprite.second.get_position().x + sprite.second.get_size().x / 2;
            int bottom_right_y = sprite.second.get_position().y + sprite.second.get_size().y / 2;
            if (top_left_x < x && x < bottom_right_x && top_left_y < y && y < bottom_right_y && _spriteClickCallbacks.find(sprite.first) != _spriteClickCallbacks.end()) {
                _spriteClickCallbacks.at(sprite.first)();
            }
        }
        for (auto &text : _texts) {
            int top_left_x = text.second.getX();
            int top_left_y = text.second.getY();
            int bottom_right_x = text.second.getX() + (text.second.getSize() * text.second.getText().size() * 0.7);
            int bottom_right_y = text.second.getY() + text.second.getSize();
            if (top_left_x < x && x < bottom_right_x && top_left_y < y && y < bottom_right_y && _textClickCallbacks.find(text.first) != _textClickCallbacks.end()) {
                _textClickCallbacks.at(text.first)();
            }
        }
    }
    if (_is_keyboard_binded_to_text) {
        char c = _window.get_char_pressed();
        if (c > 0 && _texts.at(_keyboard_bound_id).getText().size() < 20) {
            _texts.at(_keyboard_bound_id).setText(_texts.at(_keyboard_bound_id).getText() + static_cast<char>(c));
        }
    }
    for (auto keyboardCallback : _keyBindingsPressed) {
        if (_window.is_key(raylib::Window::PRESSED, static_cast<int>(keyboardCallback.first))) {
            keyboardCallback.second();
        }
    }
    for (auto keyboardCallback : _keyBindingsReleased) {
        if (_window.is_key(raylib::Window::RELEASED, keyboardCallback.first)) {
            keyboardCallback.second();
        }
    }
    // std::cout << _mustClear << std::endl;
    if (_mustClear == true) {
        _clearElements();
        _mustClear = false;
    }
    _window.start_drawing();
    auto time = std::chrono::high_resolution_clock::now();
    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - _last_frame_time).count();

    for (auto &background : _backgrounds) {
        if (time_diff > 0) {
            background.second.update_position(time_diff);
        }
        background.second.draw();
    }
    if (time_diff > 0) {
        _last_frame_time = time;
    }
    for (auto &sprite : _sprites)
        sprite.second.draw();
    for (auto &music : _musics)
        music.second.play();
    for (auto &text : _texts)
        text.second.draw();
    _window.end_drawing();
}

uint64_t GraphicsManager::addSprite(raylib::Sprite const &sprite)
{
    uint64_t id = 0;
    for (id = 0; id < std::numeric_limits<uint64_t>::max(); id++) {
        if (_sprites.find(id) == _sprites.end()) {
            _sprites.emplace(id, sprite);
            break;
        }
    }
    return id;
}

uint64_t GraphicsManager::addMusic(raylib::RayMusic const &music)
{
    uint64_t id = 0;
    for (id = 0; id < std::numeric_limits<uint64_t>::max(); id++) {
        if (_musics.find(id) == _musics.end()) {
            _musics.emplace(id, music);
            break;
        }
    }
    return id;
}

uint64_t GraphicsManager::addBackground(Background const &background)
{
    uint64_t id = 0;
    for (id = 0; id < std::numeric_limits<uint64_t>::max(); id++) {
        if (_backgrounds.find(id) == _backgrounds.end()) {
            _backgrounds.emplace(id, background);
            break;
        }
    }
    return id;
}

uint64_t GraphicsManager::addText(raylib::RayText const &text)
{
    uint64_t id = 0;
    for (id = 0; id < std::numeric_limits<uint64_t>::max(); id++) {
        if (_texts.find(id) == _texts.end()) {
            _texts.emplace(id, text);
            break;
        }
    }
    return id;
}

void GraphicsManager::removeSprite(uint64_t id)
{
    if (_sprites.find(id) == _sprites.end()) {
        return;
    }
    _sprites.erase(id);
    if (_spriteClickCallbacks.find(id) != _spriteClickCallbacks.end()) {
        _spriteClickCallbacks.erase(id);
    }
}

void GraphicsManager::removeMusic(uint64_t id)
{
    if (_musics.find(id) == _musics.end()) {
        return;
    }
    _musics.erase(id);
}

void GraphicsManager::removeText(uint64_t id)
{
    if (_texts.find(id) == _texts.end()) {
        return;
    }
    _texts.erase(id);
    if (_textClickCallbacks.find(id) != _textClickCallbacks.end()) {
        _textClickCallbacks.erase(id);
    }
    if (_is_keyboard_binded_to_text && _keyboard_bound_id == id) {
        removeKeyboardBinding();
    }
}

void GraphicsManager::removeBackground(uint64_t id)
{
    if (_backgrounds.find(id) == _backgrounds.end()) {
        return;
    }
    _backgrounds.erase(id);
}

raylib::Sprite &GraphicsManager::getSprite(uint64_t id)
{
    return _sprites.at(id);
}

raylib::RayMusic &GraphicsManager::getMusic(uint64_t id)
{
    return _musics.at(id);
}

raylib::RayText &GraphicsManager::getText(uint64_t id)
{
    return _texts.at(id);
}

Background &GraphicsManager::getBackground(uint64_t id)
{
    return _backgrounds.at(id);
}

void GraphicsManager::onSpriteClick(uint64_t id, std::function<void()> callback)
{
    _spriteClickCallbacks[id] = callback;
}

void GraphicsManager::onTextClick(uint64_t id, std::function<void()> callback)
{
    _textClickCallbacks[id] = callback;
}

void GraphicsManager::bindTextToKeyboard(uint64_t id)
{
    _is_keyboard_binded_to_text = true;
    if (_texts.find(id) != _texts.end()) {
        _keyboard_bound_id = id;
    }
}

void GraphicsManager::removeKeyboardBinding()
{
    _is_keyboard_binded_to_text = false;
    _keyboard_bound_id = 0;
}

uint64_t GraphicsManager::getTextIdBinded(void)
{
    return _keyboard_bound_id;
}

void GraphicsManager::addKeyBinding(uint32_t key, bool pressed, std::function<void()> callback)
{
    if (pressed) {
        _keyBindingsPressed.emplace(key, callback);
    } else {
        _keyBindingsReleased.emplace(key, callback);
    }
}

void GraphicsManager::removeKeyBinding(uint32_t key, bool pressed)
{
    if (pressed) {
        _keyBindingsPressed.erase(key);
    } else {
        _keyBindingsReleased.erase(key);
    }
}