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
#include "Client.hpp"
#include "entity.hpp"
#include "registry.hpp"

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
        void operator()(ecs::registry &registry, ecs::entity const &e) override
        {
            (void)registry;
            (void)e;
            std::cout << "hello" << std::endl;
        }
};

void Core::process_message(const std::string &message) 
{
    if (message.empty()) return;
    std::cout << "Traitement du message : " << message << std::endl;

    char op_code = message[0];
    switch (op_code) {
        case '1': {
            int entity_type_id = std::stoi(message.substr(1, 2));
            std::cout << "entity_type_id : " << entity_type_id << std::endl;
            int entity_id = std::stoi(message.substr(3, 4));
            std::cout << "entity_id : " << entity_id << std::endl;
            std::string entity_data = message.substr(7);
            create_entity(entity_type_id, entity_id, entity_data);
            break;
        }
        case '2': {
            int entity_id = std::stoi(message.substr(1));
            delete_entity(entity_id);
            break;
        }
        case '3': {
            int entity_type_id = std::stoi(message.substr(1, 2));
            std::cout << "entity_type_id : " << entity_type_id << std::endl;
            int entity_id = std::stoi(message.substr(3, 4));
            std::cout << "entity_id : " << entity_id << std::endl;
            std::string entity_data = message.substr(7);
            update_entity(entity_id, entity_type_id, entity_data);
            break;
        }
        default:
            std::cerr << "Op-code inconnu : " << op_code << std::endl;
            break;
    }
}

void Core::create_entity(int entity_type_id, int entity_id, const std::string& entity_data) 
{
    std::cout << "Création de l'entité de type " << entity_type_id << " avec l'id " << entity_id 
              << " et les données : " << entity_data << std::endl;
    switch (entity_type_id) {
        case 1: {
            ecs::entity bg = _registry.create_entity();
            _registry.emplace_component<Background>(bg);
            _registry.get_components<Background>()[bg]->setTexture(entity_data);
            break;
        }
        case 2: {
            ecs::entity music = _registry.create_entity();
            _registry.emplace_component<raylib::RayMusic>(music, entity_data);
            break;
        }
        case 3: {
            ecs::entity sound = _registry.create_entity();
            _registry.emplace_component<raylib::RaySound>(sound, entity_data);
            break;
        }
        case 4: {
            ecs::entity sprite = _registry.create_entity();
            _registry.emplace_component<raylib::Sprite>(sprite, entity_data);
            break;
        }
        default:
            std::cerr << "Type d'entité inconnu : " << entity_type_id << std::endl;
            break;
    }

}

void Core::delete_entity(int entity_id) 
{
    std::cout << "Suppression de l'entité avec l'id " << entity_id << std::endl;
    ecs::entity entity = _registry.entity_from_index(entity_id);
    _registry.delete_entity(entity);
}

void Core::update_entity(int entity_id, int entity_type_id, const std::string& updated_data)
{
    ecs::entity entity = _registry.entity_from_index(entity_id);
    switch (entity_type_id) {
        case 1: {
            std::optional<Background> &bg = _registry.get_components<Background>()[entity];
            if (bg.has_value()) {
                bg->setTexture(updated_data);
            }
            break;
        }
        case 2: {
            std::optional<raylib::RayMusic> &music = _registry.get_components<raylib::RayMusic>()[entity];
            if (music.has_value()) {
                music->set_source(updated_data);
            }
            break;
        }
        case 3: {
            std::optional<raylib::RaySound> &sound = _registry.get_components<raylib::RaySound>()[entity];
            if (sound.has_value()) {
                sound->set_source(updated_data);
            }
            break;
        }
        case 4: {
            std::optional<raylib::Sprite> &sprite = _registry.get_components<raylib::Sprite>()[entity];
            if (sprite.has_value()) {
                sprite->set_texture(updated_data);
            }
            break;
        }
        default:
            std::cerr << "Type d'entité inconnu : " << entity_type_id << std::endl;
            break;
    }
}

int Core::run(void)
{
    ecs::entity background = _registry.create_entity();
    _registry.emplace_component<Background>(background);
    Client client;
    client.connect("localhost");


    // std::optional<Background> &bg = _registry.get_components<Background>()[background];
    // if (bg.has_value()) {
    //     bg->setTexture("./orange.png");
    //     bg->setSpeed(10);
    //     bg->resize_y(static_cast<float>(_window.get_size().second), true);
    //     bg->setWindowDimensions(_window.get_size().first, _window.get_size().second);
    //     bg->loop(true);
    //     bg->setMoveType(Background::BACKGROUND_MOVE_TYPE::PARALLAX_X);
    //     bg->setParallaxPos([this]() {
    //         return _window.get_mouse_position();
    //     });
    // }

    while (_window.is_running()) {
        std::string data = client.get_data();
        process_message(data);
        _window.start_drawing();
        _registry.run_systems();
        _window.end_drawing();
        if (_window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_SPACE)) {
            _registry.run_single_standalone_system(SystemTest());
        }
    }
    return 0;
}
