/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include "Core.hpp"

#include "Systems/SystemTime.hpp"
#include "Systems/SystemBackground.hpp"
#include "Systems/SystemSprite.hpp"

#include "isystem.hpp"
#include "AsioApi.hpp"
#include "entity.hpp"
#include "registry.hpp"


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
        }
};

void Core::process_message(const std::string &message) 
{
    if (message.empty()) return;
    std::cout << "Traitement du message : " << message << std::endl;

    int op_code_int = message[0] - '0';
    EntityOperation op_code = static_cast<EntityOperation>(op_code_int);

    auto it = _operation_functions.find(op_code);
    if (it != _operation_functions.end()) {
        it->second(const_cast<std::string &>(message));
    } else {
        std::cerr << "Op-code inconnu ou invalide : " << op_code_int << std::endl;
    }
}

void Core::handle_create_entity(EntityType entity_type, std::size_t entity_id, const std::string &entity_data)
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

void Core::create_entity(std::string &message)
{
    int entity_type_id = std::stoi(message.substr(1, 1));
    std::size_t entity_id = std::stoul(message.substr(2, 1));
    std::string entity_data = message.substr(3);

    handle_create_entity(static_cast<EntityType>(entity_type_id), entity_id, entity_data);
}

void Core::delete_entity(std::string &message) 
{
    int entity_id = std::stoi(message.substr(1));

    std::cout << "Suppression de l'entité avec l'id " << entity_id << std::endl;
    ecs::entity entity = _registry.entity_from_index(entity_id);
    _registry.delete_entity(entity);
}


template <typename T>
void Core::update_texture_component(ecs::entity entity, const std::string &texture_data)
{
    auto &component = _registry.get_components<T>()[entity];
    if (component.has_value()) {
        component->set_texture(texture_data);
    }
}

template <typename T>
void Core::update_source_component(ecs::entity entity, const std::string &source_data)
{
    auto &component = _registry.get_components<T>()[entity];
    if (component.has_value()) {
        component->set_source(source_data);
    }
}


void Core::update_entity(std::string &message) {
    int entity_type_id = std::stoi(message.substr(1, 2));
    int entity_id = std::stoi(message.substr(3, 4));
    std::string entity_data = message.substr(7);

    ecs::entity entity = _registry.entity_from_index(entity_id);
    auto it = _update_entity_functions.find(static_cast<EntityType>(entity_type_id));
    if (it != _update_entity_functions.end()) {
        it->second(entity, entity_data);
    } else {
        std::cerr << "Type d'entité inconnu : " << entity_type_id << std::endl;
    }
}

int Core::run(void)
{
    ecs::entity background = _registry.create_entity();
    _registry.emplace_component<Background>(background);
    rtype_protocol::AsioApi client;
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
        if (client.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = client.get_data();
            for (std::size_t i = 0; i < data.data.size(); i++) {
                std::cout <<  static_cast<int>(data.data[i]) << " ";
            }
            std::cout << "from " << data.sender_endpoint.address() << ":" << data.sender_endpoint.port() << std::endl;
            std::cout << std::endl;
        }
        _window.start_drawing();
        _registry.run_systems();
        if (_window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_SPACE)) {
            _registry.run_single_standalone_system(SystemTest());
        }
        _window.end_drawing();
    }
    return 0;
}
