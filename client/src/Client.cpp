/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : resolver(io_context), socket(io_context) {
    connected = false;
}

Client::~Client() 
{
    if (socket.is_open()) {
        socket.close();
    }
}

void Client::process_message(const std::string &message) 
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
            int entity_id = std::stoi(message.substr(1, 4));
            std::string updated_data = message.substr(5);
            update_entity(entity_id, updated_data);
            break;
        }
        default:
            std::cerr << "Op-code inconnu : " << op_code << std::endl;
            break;
    }
}

void Client::create_entity(int entity_type_id, int entity_id, const std::string& entity_data) 
{
    std::cout << "Création de l'entité de type " << entity_type_id << " avec l'id " << entity_id 
              << " et les données : " << entity_data << std::endl;

}

void Client::delete_entity(int entity_id) 
{
    std::cout << "Suppression de l'entité avec l'id " << entity_id << std::endl;
}

void Client::update_entity(int entity_id, const std::string& updated_data) 
{
    std::cout << "Mise à jour de l'entité " << entity_id << " avec les nouvelles données : " << updated_data << std::endl;
}


bool Client::connect(const std::string &hostname) 
{
    try {
        udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), hostname, "5000");
        endpoint = *endpoints.begin();
        socket.open(udp::v4());
        connected = true;
        std::cout << "Connexion réussie à " << hostname << " sur le port 5000." << std::endl;
        send_message("Hello from client!");
    } catch (const std::exception &e) {
        std::cerr << "Erreur de connexion : " << e.what() << std::endl;
        connected = false;
    }
    return connected;
}

void Client::send_message(const std::string &message) 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return;
    }
    try {
        socket.send_to(asio::buffer(message), endpoint);
        std::cout << "Message envoyé : " << message << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de l'envoi du message : " << e.what() << std::endl;
    }
}

bool Client::has_data() 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return false;
    }

    try {
        asio::socket_base::bytes_readable command(true);
        socket.io_control(command);
        return command.get() > 0;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la vérification des données : " << e.what() << std::endl;
        return false;
    }
}

std::string Client::get_data() 
{
    if (!connected) {
        std::cerr << "Erreur : Client non connecté !" << std::endl;
        return "";
    }

    char buffer[1024];
    udp::endpoint sender_endpoint;

    try {
        size_t reply_length = socket.receive_from(asio::buffer(buffer, 1024), sender_endpoint);
        std::string reply(buffer, reply_length);
        std::cout << "Réponse reçue : " << reply << std::endl;
        return reply;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
        return "";
    }
}
