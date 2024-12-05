/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GraphicalCore
*/

#include <memory>
#include <iterator>
#include <iostream>
#include <chrono>

#include "Raylib/RayMusic.hpp"
#include "GraphicalCore.hpp"

GraphicalCore::GraphicalCore(std::size_t win_width, std::size_t win_height) :
    _music(), _window(win_width, win_height), _audio_device(), _last_update(std::chrono::system_clock::now())
{
}

GraphicalCore::~GraphicalCore()
{
}

void GraphicalCore::start_draw(void)
{
    using Clock = std::chrono::high_resolution_clock;
    auto now = Clock::now(); // Temps actuel avec haute résolution

    // Calculer le temps écoulé depuis la dernière mise à jour
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_update).count();
    this->_last_update = now;

    if (this->_music != nullptr) {
        this->_music->play();
    }

    this->_window.start_drawing();
    this->_window.clear();

    for (auto &background : this->_backgrounds) {
        background.update_position(elapsed); // elapsed est en millisecondes
        background.draw();
    }

    std::cout << "time elapsed: " << elapsed << " ms" << std::endl;
}

void GraphicalCore::stop_draw(void)
{
    this->_window.end_drawing();
}

void GraphicalCore::insertBackground(Background &&background, std::size_t position)
{
    if (position > this->_backgrounds.size()) {
        this->_backgrounds.emplace_back();
        return;
    }
    this->_backgrounds.emplace(std::next(this->_backgrounds.begin(), position), std::move(background));
}

void GraphicalCore::removeBackground(std::size_t position)
{
    if (position >= this->_backgrounds.size()) {
        throw std::out_of_range("Position hors de la liste.");
    }

    auto it = std::next(this->_backgrounds.begin(), position);
    this->_backgrounds.erase(it);
}

void GraphicalCore::setMusic(std::string const &path)
{
    this->_music.reset();
    this->_music = std::make_unique<raylib::RayMusic>(path);
}

void GraphicalCore::clearBackgrounds(void)
{
    this->_backgrounds.clear();
}

Background &GraphicalCore::getBackground(std::size_t position)
{
    if (position >= this->_backgrounds.size()) {
        throw std::out_of_range("Position hors de la liste.");
    }

    return *std::next(this->_backgrounds.begin(), position);
}

raylib::Window const &GraphicalCore::getConstWindow(void) const
{
    return this->_window;
}


raylib::Window &GraphicalCore::getWindow(void)
{
    return this->_window;
}

std::unique_ptr<raylib::RayMusic> & GraphicalCore::getMusic(void)
{
    return this->_music;
}

float GraphicalCore::getElapsedTime(void) const
{
    return this->_elapsed;
}
