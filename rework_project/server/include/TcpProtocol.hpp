/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TCPPROTOCOL
*/

#include "Client.hpp"
#include "IGame.hpp"
#include "TcpServer.hpp"
#include "Room.hpp"
#include <memory>
#include <map>
#include <functional>

#ifndef TCPPROTOCOL_HPP_
    #define TCPPROTOCOL_HPP_

class TcpProtocol {
    public:
        TcpProtocol(
            std::map<uint8_t, Room> &rooms,
            std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &clients,
            TcpServer &tcpServer
        );
        ~TcpProtocol();

        int interpreter(std::shared_ptr<asio::ip::tcp::socket> &client, std::vector<uint8_t> data);
        void listRooms(std::shared_ptr<asio::ip::tcp::socket> &client);
        void enterRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId);
        void createRoom(std::shared_ptr<asio::ip::tcp::socket> &client, std::string roomName, std::string gameName);
        void exitRoom(std::shared_ptr<asio::ip::tcp::socket> &client);
        void renameRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId, std::string roomName);
        void deleteRoom(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t roomId);
        std::vector<uint8_t> image_to_binary(const std::string &path);
        void sendImage(std::shared_ptr<asio::ip::tcp::socket> &client, uint8_t spriteId, uint32_t sizeX, uint32_t sizeY, uint32_t width, uint32_t height,
    uint32_t offsetX, uint32_t offsetY, uint8_t nbFrames, uint32_t frameDelay, const std::string &path);

    private:
        std::unordered_map<uint8_t, std::function<void(std::shared_ptr<asio::ip::tcp::socket> &, std::istringstream&)>> _commandMap;

        std::map<uint8_t, Room> &_rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> &_clients;
        TcpServer &_tcpServer;

        void copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value);

};

#endif /* !TCPPROTOCOL_HPP_ */
