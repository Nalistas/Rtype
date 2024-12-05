/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include "Core.hpp"
#include "Background.hpp"
#include "Raylib/RayMusic.hpp"
#include "Raylib/RaySound.hpp"
#include "Raylib/Sprite.hpp"


#include "Systems/SystemTime.hpp"
#include "Systems/SystemBackground.hpp"
#include "Systems/SystemSprite.hpp"

#include "isystem.hpp"

#include <iostream>

Core::Core(std::size_t win_width, std::size_t win_height):
    _window(win_width, win_height)
{
    _registry.register_component<raylib::RayMusic>();
    _registry.register_component<raylib::RaySound>();
    _registry.register_component<Background>();
    _registry.register_component<raylib::Sprite>();

    _registry.add_standalone_system(SystemTime(this->time));
    _registry.add_system<Background>(SystemBackground(this->time));
    _registry.add_system<raylib::Sprite>(SystemSprite());
}

Core::~Core()
{
}

class SystemTest : public ecs::isystem<> {
    public:
        void operator()(ecs::iregistry &registry, ecs::entity const &e) override
        {
            (void)registry;
            (void)e;
            std::cout << "hello" << std::endl;
        }
};

int Core::run(void)
{
    ecs::entity background = _registry.create_entity();
    _registry.emplace_component<Background>(background);

    std::optional<Background> &bg = _registry.get_components<Background>()[background];
    if (bg.has_value()) {
        bg->setTexture("./orange.png");
        bg->setSpeed(10);
        bg->resize_y(static_cast<float>(_window.get_size().second), true);
        bg->setWindowDimensions(_window.get_size().first, _window.get_size().second);
        bg->loop(true);
        bg->setMoveType(Background::BACKGROUND_MOVE_TYPE::PARALLAX_X);
        bg->setParallaxPos([this]() {
            return _window.get_mouse_position();
        });
    }

    while (_window.is_running()) {
        _window.start_drawing();
        _registry.run_systems();
        _window.end_drawing();
        if (_window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_ESCAPE)) {
            _registry.run_single_standalone_system(SystemTest());
        }
    }
    return 0;
}
