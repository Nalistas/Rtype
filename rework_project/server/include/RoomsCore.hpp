/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include <string>
#include <map>
#include "TcpServer.hpp"

#ifndef CORE_HPP_
    #define CORE_HPP_


class RoomsCore {
    public:
        RoomsCore(std::string const &port);
        ~RoomsCore();

        void run(void);

    private:
        TcpServer _tcpServer;
        std::map<std::size_t, std::string> _rooms;
};

#endif /* !CORE_HPP_ */
