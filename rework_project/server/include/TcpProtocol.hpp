/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TCPPROTOCOL
*/

#include "registry.hpp"
#include "IGame.hpp"
#include "TcpServer.hpp"
#include <memory>
#include <map>
#include <functional>

#ifndef TCPPROTOCOL_HPP_
    #define TCPPROTOCOL_HPP_

class TcpProtocol {
    public:
        TcpProtocol(TcpServer &tcpServer);
        ~TcpProtocol();

        int interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data);
        void listRooms(std::shared_ptr<asio::ip::tcp::socket> client);
        void enterRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId);
        void createRoom(std::shared_ptr<asio::ip::tcp::socket> client, std::string roomName, std::string gameName);
        void exitRoom(std::shared_ptr<asio::ip::tcp::socket> client);
        void renameRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId, std::string roomName);
        void deleteRoom(std::shared_ptr<asio::ip::tcp::socket> client, int roomId);
        std::vector<char> image_to_binary(const std::string &path);
        void sendImage(std::shared_ptr<asio::ip::tcp::socket> client, uint8_t spriteId, uint32_t sizeX, uint32_t sizeY, uint32_t width, uint32_t height,
    uint32_t offsetX, uint32_t offsetY, uint8_t nbFrames, uint32_t frameDelay, const std::string &path);

    private:
        ecs::registry _registry;
        std::unordered_map<char, std::function<void(std::shared_ptr<asio::ip::tcp::socket>, std::istringstream&)>> _commandMap;
        TcpServer &_tcpServer;

};

#endif /* !TCPPROTOCOL_HPP_ */
