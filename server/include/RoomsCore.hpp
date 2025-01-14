/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include <string>
#include <map>
#include "TcpServer.hpp"
#include "TcpProtocol.hpp"
#include "Room.hpp"
#include "Client.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_


class RoomsCore {
    public:
        /**
         * @brief Construct a new Rooms Core object
         * @param port the port of the server
         */
        RoomsCore(std::string const &port);

        /**
         * @brief Destroy the Rooms Core object
         */
        ~RoomsCore();

        /**
         * @brief Run the rooms core
         */
        void run(void);

    private:
        /**
         * @brief Check if there are new clients
         */
        void checkNewClients(void);

        /**
         * @brief Check if there are new clients
         */
        void checkClients(TcpProtocol &tcpProtocol);

        /**
         * @brief Treat a client command
         */
        void treatClient(std::shared_ptr<asio::ip::tcp::socket> &client, TcpProtocol &tcpProtocol);

        TcpServer _tcpServer;
        std::map<uint8_t, Room> _rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> _clients;
};

#endif /* !CORE_HPP_ */
