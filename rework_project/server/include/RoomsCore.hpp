/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include <string>
#include <map>
#include "TcpServer.hpp"
#include "Room.hpp"
#include "Client.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_


class RoomsCore {
    public:
        RoomsCore(std::string const &port);
        ~RoomsCore();

        void run(void);

    private:
        TcpServer _tcpServer;
        std::map<uint8_t, Room> _rooms;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, Client> _clients;
};

#endif /* !CORE_HPP_ */
