/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RtypeBuilder
*/

#include "RtypeBuilder.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <array>

RtypeBuilder::RtypeBuilder()
{
}

RtypeBuilder::~RtypeBuilder()
{
}

Rtype_sc RtypeBuilder::build(std::string const &config_path)
{
    Rtype_sc rtype_sc;
    if (this->config(config_path, rtype_sc) != 0) {
        throw std::runtime_error("Error in config file");
    }
    return rtype_sc;
}


std::string RtypeBuilder::trim(const std::string& str) const
{
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos) return ""; // Chaîne vide si uniquement des espaces
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}


std::unordered_map<std::string, std::string> RtypeBuilder::get_data(std::string const &config_path) const
{
    std::ifstream file(config_path);
    if (!file.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        throw std::runtime_error("Unable to open file.");
    }

    std::unordered_map<std::string, std::string> data;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            data[trim(key)] = trim(value);
        }
    }

    file.close();
    return data;
}



int RtypeBuilder::config(std::string const &config_path, Rtype_sc &rtype_sc)
{
    std::unordered_map<std::string, std::string> data;

    try {
        data = this->get_data(config_path);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }

    auto it = data.find("type");
    if (it != data.end()) {
        if (it->second != "server" && it->second != "client") {
            std::cerr << "Error: type must be server or client." << std::endl;
            return 84;
        }
        if (it->second == "server") {
            rtype_sc._is_server = true;
        }
        if (it->second == "client") {
            rtype_sc._is_server = false;
        }
    } else {
        std::cerr << "Error: type not found in config file." << std::endl;
        return 84;
    }
    rtype_sc._server_ip = data["ip"];
    std::cout << "Server IP: " << rtype_sc._server_ip << std::endl;
    rtype_sc._tcp_server_port = data["tcp_port"];
    rtype_sc._udp_server_port = data["udp_port"];
    rtype_sc._game = data["game"];
    rtype_sc._graphics = data["graphics"];
    return 0;
}

