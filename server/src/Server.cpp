/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "Systems/SpriteSystem.hpp"
#include <string>

#include "SafeDirectoryLister.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"
#include "GraphicsPrimitives.hpp"

std::size_t endpoint_hash_class::operator()(const udp::endpoint &ep) const {
    return std::hash<std::string>()(ep.address().to_string() + ":" + std::to_string(ep.port()));
}

Server::~Server() {}

Server::Server() 
    : _time(0), _api()
{


    SafeDirectoryLister sd;
    sd.open(".", false);

    #if defined(WIN32) || defined(_WIN32)
        _dll.open("./libRtype.dll");
    #else
        _dll.open("./libRtype.so");
    #endif
    
    _game = _dll.getSym("gameElement");

    _registry = std::make_shared<ecs::registry>();
    _registry->register_component<graphics_interface::Sprite>();
    _registry->register_component<graphics_interface::Background>();
    _registry->register_component<graphics_interface::Music>();
    _registry->register_component<graphics_interface::Sound>();
    _registry->add_system<graphics_interface::Sprite>(SpriteSystem(this->_time));

    _game->setBroadcastCreate(std::bind(&Server::broadcastCreate, this, std::placeholders::_1));
    _game->setBroadcastDelete(std::bind(&Server::broadcastDelete, this, std::placeholders::_1));
    _game->setBroadcastUpdate(std::bind(&Server::broadcastUpdate, this, std::placeholders::_1));
    _game->setRegistry(_registry);

    std::vector<rtype::ClientAction> actions = _game->getClientActionHandlers();
    this->set_actions(actions);

    _api.start_server("5000");
}

int Server::loop() 
{
    while (true) {
        if (_api.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = _api.get_data();

            if (_clients.find(data.sender_endpoint) == _clients.end()) {
                this->setNewClient(data.sender_endpoint);
            } else {
                this->processMessage(data);
            }
        }
    }

    return 0;
}


void Server::set_actions(std::vector<rtype::ClientAction> &actions)
{
    for (std::size_t i = 0; i < actions.size(); i++) {
        _keys[actions[i].key] = std::make_pair(_handlers.size(), actions[i].pressed);
        if (actions[i].handler) {
            _handlers.push_back(std::move(actions[i].handler));
        }
    }
}

void Server::setNewClient(udp::endpoint const &endpoint)
{
    int id_client = this->_game->createPlayer();
    this->_clients[endpoint] = id_client;
    this->_reverse_clients[id_client] = endpoint;

    this->updateScreen(id_client);
    this->setClientAction(id_client);
}

void Server::sendToClient(std::size_t id, std::vector<char> const &data)
{
    udp::endpoint endpoint = this->_reverse_clients[id];
    rtype_protocol::AsioApi::UDP_DATA client_data;

    client_data.data = data;
    client_data.sender_endpoint = endpoint;
    _api.reply_to(client_data);
}





/////////////////////////////////////////////////////////////////////////////
//
//      HANDLE MESSAGE FROM CLIENT
//
/////////////////////////////////////////////////////////////////////////////




void Server::setClientAction(std::size_t id_client)
{
    // [key] [state (1 = pressed, 2 = released)] [id action that will be sent to the serv]
    // [SIZE][ACTION][ID1][ID2][ID3][ID4][KEY1][KEY2][KEY3][KEY4][pressed]
    // 
    std::vector<char> data;

    data.resize(11);
    data[0] = 11;
    data[1] = static_cast<char>(EntityOperation::ACTION);

    for (auto key_binding: _keys) {
        unsigned int id_action = key_binding.first;
        unsigned int key_code = key_binding.second.first;
        bool pressed = key_binding.second.second;

        std::memcpy(&data[2], &id_action, sizeof(id_action));
        std::memcpy(&data[6], &key_code, sizeof(key_code));
        data[10] = static_cast<char>(pressed);
        this->sendToClient(id_client, data);
    }
}



void Server::processMessage(rtype_protocol::AsioApi::UDP_DATA const &data)
{
    // [SIZE][ID_ACTION1][ID_ACTION2][ID_ACTION3][ID_ACTION4][X_POS1][X_POS2][X_POS3][X_POS4][Y_POS1][Y_POS2][Y_POS3][Y_POS4]
    std::size_t id_client = this->_clients[data.sender_endpoint];
    unsigned int id_action = 0;
    unsigned int mouse_x = 0;
    unsigned int mouse_y = 0;
    unsigned char size = data.data[0];

    std::memcpy(&id_action, &data.data[1], sizeof(id_action));
    std::memcpy(&mouse_x, &data.data[5], sizeof(mouse_x));
    std::memcpy(&mouse_y, &data.data[9], sizeof(mouse_y));

    (*(this->_handlers[id_action]))(id_client, mouse_x, mouse_y);
}



/////////////////////////////////////////////////////////////////////////////
//
//      BROADCAST
//
/////////////////////////////////////////////////////////////////////////////




void Server::broadcastDelete(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;

    data.data = std::vector<char>();
    data.data.resize(2 + sizeof(entity));
    data.data[0] = static_cast<char>(3);
    data.data[1] = static_cast<char>(EntityOperation::REMOVE);

    memcpy(&data.data[2], &entity, sizeof(entity));

    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        data.sender_endpoint = it->first;
        _api.reply_to(data);
    }
}

void Server::broadcast(char op_code, char entity_type, ecs::entity const &entity, std::vector<char> const &data)
{
    rtype_protocol::AsioApi::UDP_DATA client_data;
    client_data.data = data;
    client_data.data.insert(client_data.data.begin(), static_cast<char>(entity));
    client_data.data.insert(client_data.data.begin(), entity_type);
    client_data.data.insert(client_data.data.begin(), static_cast<char>(op_code));
    client_data.data.insert(client_data.data.begin(), data.size());

    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        client_data.sender_endpoint = it->first;
        _api.reply_to(client_data);
    }
}

void Server::broadcastCreate(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;
    char op_code = static_cast<char>(EntityOperation::CREATE);

    auto& music_components = _registry->get_components<graphics_interface::Music>();
    if (entity < music_components.size()) {
        auto music = music_components[entity];
        if (music.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), entity, (*music).encode());
        }
    }

    auto& sound_components = _registry->get_components<graphics_interface::Sound>();
    if (entity < sound_components.size()) {
        auto sound = sound_components[entity];
        if (sound.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::SOUND), entity, (*sound).encode());
        }
    }

    auto& sprite_components = _registry->get_components<graphics_interface::Sprite>();
    if (entity < sprite_components.size()) {
        auto sprite = sprite_components[entity];
        if (sprite.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::SPRITE), entity, (*sprite).encode());
        }
    }

    auto& bg_components = _registry->get_components<graphics_interface::Background>();
    if (entity < bg_components.size()) {
        auto bg = bg_components[entity];
        if (bg.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::BACKGROUND), entity, (*bg).encode());
        }
    }
}

void Server::broadcastUpdate(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;
    char op_code = static_cast<char>(EntityOperation::UPDATE);

    auto& music_components = _registry->get_components<graphics_interface::Music>();
    if (entity < music_components.size()) {
        auto music = music_components[entity];
        if (music.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), entity, (*music).encode());
        }
    }

    auto& sound_components = _registry->get_components<graphics_interface::Sound>();
    if (entity < sound_components.size()) {
        auto sound = sound_components[entity];
        if (sound.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::SOUND), entity, (*sound).encode());
        }
    }

    auto& sprite_components = _registry->get_components<graphics_interface::Sprite>();
    if (entity < sprite_components.size()) {
        auto sprite = sprite_components[entity];
        if (sprite.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::SPRITE), entity, (*sprite).encode());
        }
    }

    auto& bg_components = _registry->get_components<graphics_interface::Background>();
    if (entity < bg_components.size()) {
        auto bg = bg_components[entity];
        if (bg.has_value()) {
            this->broadcast(op_code, static_cast<char>(EntityType::BACKGROUND), entity, (*bg).encode());
        }
    }
}







//////////////////////////////////////////////////////////////////////////////
//
//      UPDATE
//
/////////////////////////////////////////////////////////////////////////////





void Server::updateScreen(std::size_t id_client)
{
    udp::endpoint endpoint = this->_reverse_clients[id_client];

    auto &musics = _registry->get_components<graphics_interface::Music>();
    auto &sounds = _registry->get_components<graphics_interface::Sound>();
    auto &sprites = _registry->get_components<graphics_interface::Sprite>();
    auto &bgs = _registry->get_components<graphics_interface::Background>();

    rtype_protocol::AsioApi::UDP_DATA data;

    std::vector<char> base({0, static_cast<char>(EntityOperation::CREATE), static_cast<char>(EntityType::MUSIC), 0});

    std::size_t i = 0;
    for (auto it = musics.begin(); it != musics.end(); it++) {
        if (it->has_value()) {
            data.data = base;
            data.data[3] = static_cast<char>(i);

            std::vector<char> music_data = it->value().encode();
            data.data.insert(data.data.end(), music_data.begin(), music_data.end());
            data.sender_endpoint = endpoint;
            _api.reply_to(data);
        }
        i++;
    }

    base[2] = static_cast<char>(EntityType::BACKGROUND);
    i = 0;
    for (auto it = bgs.begin(); it != bgs.end(); it++) {
        if (it->has_value()) {
            data.data = base;
            data.data[3] = static_cast<char>(i);
            std::vector<char> bg_data = it->value().encode();
            data.data.insert(data.data.end(), bg_data.begin(), bg_data.end());
            data.sender_endpoint = endpoint;
            _api.reply_to(data);
        }
        i++;
    }

    base[2] = static_cast<char>(EntityType::SPRITE);
    i = 0;
    for (auto it = sprites.begin(); it != sprites.end(); it++) {
        if (it->has_value()) {
            data.data = base;
            data.data[3] = static_cast<char>(i);
            std::vector<char> sprite_data = it->value().encode();
            data.data.insert(data.data.end(), sprite_data.begin(), sprite_data.end());
            data.sender_endpoint = endpoint;
            _api.reply_to(data);
        }
        i++;
    }

    base[2] = static_cast<char>(EntityType::SOUND);
    i = 0;
    for (auto it = sounds.begin(); it != sounds.end(); it++) {
        if (it->has_value()) {
            data.data = base;
            data.data[3] = static_cast<char>(i);
            std::vector<char> sound_data = it->value().encode();
            data.data.insert(data.data.end(), sound_data.begin(), sound_data.end());
            data.sender_endpoint = endpoint;
            _api.reply_to(data);
        }
        i++;
    }
}

