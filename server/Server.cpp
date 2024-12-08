/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

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
    io_context.run();
    return 0;
}
