/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <string>


std::size_t endpoint_hash_class::operator()(const udp::endpoint &ep) const {
    return std::hash<std::string>()(ep.address().to_string() + ":" + std::to_string(ep.port()));
}


Server::Server() 
    : socket(io_context, udp::endpoint(udp::v4(), 5000)) 
{
    start_receive();
}

Server::~Server() 
{
}

void Server::send_create_entity(udp::endpoint client_endpoint, EntityType entity_type, int entity_id, const std::string& entity_data) 
{
    std::string message = std::to_string(static_cast<int>(EntityOperation::CREATE)) + 
                          std::to_string(static_cast<int>(entity_type)) + 
                          std::to_string(entity_id) + 
                          entity_data;

    socket.send_to(asio::buffer(message), client_endpoint);
}

void Server::send_delete_entity(udp::endpoint client_endpoint, int entity_id) 
{
    std::string message = std::to_string(static_cast<int>(EntityOperation::DELETE)) + 
                          std::to_string(entity_id);

    socket.send_to(asio::buffer(message), client_endpoint);
}


void Server::send_update_entity(udp::endpoint client_endpoint, EntityType entity_type, int entity_id, const std::string& updated_data) 
{
    std::string message = std::to_string(static_cast<int>(EntityOperation::UPDATE)) + 
                          std::to_string(static_cast<int>(entity_type)) + 
                          std::to_string(entity_id) + 
                          updated_data;

    socket.send_to(asio::buffer(message), client_endpoint);
}

void Server::start_receive()
{
    socket.async_receive_from(
        asio::buffer(recv_buffer), sender_endpoint_,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::string message(recv_buffer.data(), bytes_recvd);
                handle_receive(message);
            }
            start_receive();
        }
    );
}

void Server::handle_receive(const std::string& message) 
{
    std::cout << "Message reçu de " << sender_endpoint_.address().to_string()
              << ":" << sender_endpoint_.port() << " -> " << message << std::endl;

    if (clients.find(sender_endpoint_) == clients.end()) {
        send_create_entity(sender_endpoint_, EntityType::BACKGROUND, 1, "./orange.png");
        clients.insert(sender_endpoint_);
    }
}

int Server::loop() 
{
    while (true) {
        char data[1024];
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(asio::buffer(data, 1024), sender_endpoint);

        std::string message(data, length);
        std::cout << "Message reçu de " << sender_endpoint.address().to_string()
                  << ":" << sender_endpoint.port() << " -> " << message << std::endl;

        // add client if not exist
        if (clients.find(sender_endpoint) == clients.end()) {
            clients.insert(sender_endpoint);
            std::cout << "Nouveau client ajouté : " 
                      << sender_endpoint.address().to_string()
                      << ":" << sender_endpoint.port() << std::endl;
        }

        // Préparer une réponse
        std::string reply = "Echo: " + message;
        socket.send_to(asio::buffer(reply), sender_endpoint);
    }

    return 0;
}
