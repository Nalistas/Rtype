/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

#include "Core.hpp"

#include "Systems/SystemTime.hpp"
#include "Systems/SystemBackground.hpp"
#include "Systems/SystemSprite.hpp"
#include "Systems/SystemAnimation.hpp"
#include "Systems/SystemAutoDestructTimer.hpp"
#include "Systems/SystemSpeed.hpp"

#include "isystem.hpp"
#include "AsioApi.hpp"
#include "entity.hpp"
#include "registry.hpp"
#include "Speed.hpp"
#include "AutoDestructTimer.hpp"
#include "Animation.hpp"


Core::Core(std::size_t win_width, std::size_t win_height):
    _window(win_width, win_height)
{
    _registry.register_component<raylib::RayMusic>();
    _registry.register_component<raylib::RaySound>();
    _registry.register_component<Background>();
    _registry.register_component<raylib::Sprite>();
    _registry.register_component<AutoDestructTimer>();
    _registry.register_component<Speed>();
    _registry.register_component<Animation>();

    _registry.add_standalone_system(SystemTime(this->time));
    _registry.add_system<Background>(SystemBackground(this->time));
    _registry.add_system<raylib::Sprite>(SystemSprite());
    _registry.add_system<Speed, raylib::Sprite>(SystemSpeed(this->time));
    _registry.add_system<Animation, raylib::Sprite>(SystemAnimation(this->time));
    _registry.add_system<AutoDestructTimer>(SystemAutoDestructTimer());
}

Core::~Core()
{
}

//////////////////////////////////////////////////////////
//
// Functions related to message processing
//
//////////////////////////////////////////////////////////


void Core::process_message(const std::vector<char> &message) 
{
    if (message.empty()) return;
    std::cout << "Traitement du message : ";
    for (char c : message) std::cout << c;
    std::cout << std::endl;

    EntityOperation op_code = static_cast<EntityOperation>(message[1]);
    std::cout << "Op-code : " << static_cast<int>(op_code) << std::endl;

    auto it = _operation_functions.find(op_code);
    if (it != _operation_functions.end()) {
        it->second(const_cast<std::vector<char> &>(message));
    } else {
        std::cerr << "Op-code inconnu ou invalide : " << static_cast<int>(op_code) << std::endl;
    }
}

//////////////////////////////////////////////////////////
//
// Functions related to message processing
//
//////////////////////////////////////////////////////////


////////////////////////////////////////
// Create entity
////////////////////////////////////////

void Core::handle_create_entity(EntityType entity_type, std::size_t entity_id, const std::vector<char> &entity_data)
{
    ecs::entity entity = _registry.entity_from_index(entity_id);

    std::cout << "Création de l'entité avec l'id " << entity_id << std::endl;

    auto it = _create_entity_functions.find(entity_type);
    if (it != _create_entity_functions.end()) {
        it->second(entity, entity_data);
        std::cout << "Création de l'entité avec l'id " << entity_id << " fini !" << std::endl;
    } else {
        std::cerr << "Type d'entité inconnu : " << static_cast<int>(entity_type) << std::endl;
    }
}



void Core::create_entity(std::vector<char> &message)
{
    EntityType entity_type = static_cast<EntityType>(message[2]);
    std::size_t entity_id = static_cast<std::size_t>(message[3]);
    std::vector<char> entity_data(message.begin() + 4, message.end());

    handle_create_entity(entity_type, entity_id, entity_data);
}



////////////////////////////////////////
// Delete entity
////////////////////////////////////////

void Core::delete_entity(std::vector<char> &message) 
{
    int entity_id = static_cast<int>(message[2]);

    std::cout << "Suppression de l'entité avec l'id " << entity_id << std::endl;
    ecs::entity entity = _registry.entity_from_index(entity_id);
    _registry.delete_entity(entity);
}


////////////////////////////////////////
// Update entity
////////////////////////////////////////

void Core::update_sprite_component(ecs::entity entity, const std::vector<char> &entity_data)
{
    auto &component = _registry.get_components<raylib::Sprite>()[entity];
    if (component.has_value()) {
        graphics_interface::Sprite sprite;
        sprite.decode(entity_data);
        component->setComponent(sprite);
    }
}

void Core::update_background_component(ecs::entity entity, const std::vector<char> &entity_data)
{
    auto &component = _registry.get_components<Background>()[entity];
    if (component.has_value()) {
        graphics_interface::Background bg;
        bg.decode(entity_data);
        component->setComponent(bg);
    }
}

void Core::update_music_component(ecs::entity entity, const std::vector<char> &entity_data)
{
    auto &component = _registry.get_components<raylib::RayMusic>()[entity];
    if (component.has_value()) {
        graphics_interface::Music music;
        music.decode(entity_data);
        component->set_source(music.path);
    }
}

void Core::update_sound_component(ecs::entity entity, const std::vector<char> &entity_data)
{
    auto &component = _registry.get_components<raylib::RaySound>()[entity];
    if (component.has_value()) {
        graphics_interface::Sound sound;
        sound.decode(entity_data);
        component->set_source(sound.path);
    }
}

void Core::update_entity(std::vector<char> &message) {
    EntityType entity_type = static_cast<EntityType>(message[1]);
    std::size_t entity_id = static_cast<std::size_t>(message[2]);
    std::vector<char> entity_data(message.begin() + 3, message.end());

    ecs::entity entity = _registry.entity_from_index(entity_id);
    auto it = _update_entity_functions.find(entity_type);
    if (it != _update_entity_functions.end()) {
        it->second(entity, entity_data);
    } else {
        std::cerr << "Type d'entité inconnu : " << static_cast<int>(entity_type) << std::endl;
    }
}

////////////////////////////////////////
// Related to the actions
////////////////////////////////////////

void Core::set_actions(std::vector<char> const &actions)
{
    // [SIZE][ACTION][ID1][ID2][ID3][ID4][KEY1][KEY2][KEY3][KEY4][PRESSED]
    char size = static_cast<char>(actions[0]);

    unsigned int id_action = 0;
    unsigned int key_code = 0;
    bool pressed = false;

    std::memcpy(&id_action, &actions[2], sizeof(id_action));
    std::memcpy(&key_code, &actions[6], sizeof(key_code));
    pressed = static_cast<bool>(actions[10]);

    if (pressed) {
        _on_key_pressed[key_code] = id_action;
    } else {
        _on_key_released[key_code] = id_action;
    }
}


void Core::send_action(unsigned int id_action)
{
    // [SIZE][ID_ACTION1][ID_ACTION2][ID_ACTION3][ID_ACTION4][X_POS1][X_POS2][X_POS3][X_POS4][Y_POS1][Y_POS2][Y_POS3][Y_POS4]
    std::vector<char> data;
    raylib::Vector2 mouse_pos = _window.get_mouse_position();
    unsigned int mouse_x = static_cast<unsigned int>(mouse_pos.x);
    unsigned int mouse_y = static_cast<unsigned int>(mouse_pos.y);

    data.resize(13);
    data[0] = 13;

    std::memcpy(&data[1], &id_action, sizeof(id_action));
    std::memcpy(&data[5], &mouse_x, sizeof(mouse_x));
    std::memcpy(&data[9], &mouse_y, sizeof(mouse_y));

    this->_api.send_message(data);
}

//////////////////////////////////////////////////////////
//
// Functions related to the window
//
//////////////////////////////////////////////////////////



int Core::run(void)
{
    _api.connect("localhost");

    while (_window.is_running()) {
        if (_api.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = _api.get_data();
            std::cout << "Réception de données : ";
            for (std::size_t i = 0; i < data.data.size(); i++) {
                std::cout <<  static_cast<int>(data.data[i]) << " ";
            }
            std::cout << "from " << data.sender_endpoint.address() 
                      << ":" << data.sender_endpoint.port() << std::endl;
            std::cout << std::endl;

            process_message(data.data);
        }

        _window.start_drawing();
        _window.clear({255, 255, 255, 255});
        _registry.run_systems();
        _window.end_drawing();
        for (auto &pair : _on_key_pressed) {
            if (_window.is_key(raylib::Window::BUTTON_STATE::PRESSED, pair.first)) {
            }
        }
        for (auto &pair : _on_key_released) {
            if (_window.is_key(raylib::Window::BUTTON_STATE::RELEASED, pair.first)) {
            }
        }
    }
    return 0;
}
