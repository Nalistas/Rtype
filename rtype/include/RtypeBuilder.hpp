/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Configure
*/

#include <string>
#include <unordered_map>
#include "Rtype_sc.hpp"

#ifndef RTYPE_BUILDER_HPP_
    #define RTYPE_BUILDER_HPP_

struct client_config {
    std::string name;
    std::string ip;
    int port;
};

struct server_config {
    std::string game;
    std::string ip;
    int tcpport;
    int gport;
};

class RtypeBuilder {
    public:
        RtypeBuilder();
        ~RtypeBuilder();

        Rtype_sc build(std::string const &config_path);
        std::string trim(const std::string& str) const;
        std::unordered_map<std::string, std::string> get_data(std::string const &config_path) const;
        int config(std::string const &config_path, Rtype_sc &rtype_sc);


    private:
};

#endif /* !RTYPE_BUILDER_HPP_ */
