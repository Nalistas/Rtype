/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Rtype_sc
*/

#include <string>
#include <unordered_map>

#ifndef Rtype_sc_HPP_
    #define Rtype_sc_HPP_

class RtypeBuilder;

class Rtype_sc {
    public:
        Rtype_sc();
        ~Rtype_sc();

        friend class RtypeBuilder;

    private:
        bool _running;
        bool _is_server;
        std::string _server_ip;
        std::string _tcp_server_port;
        std::string _udp_server_port;
        std::string _game;
        std::string _graphics;
};

#endif /* !Rtype_sc_HPP_ */
