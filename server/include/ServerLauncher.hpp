/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/


#ifndef SERVER_LAUNCHER_HPP_
    #define SERVER_LAUNCHER_HPP_

    #include "RoomsCore.hpp"

/**
 * @brief The ServerLauncher class
 * This class allows to launch a server
 */
class ServerLauncher {
    public:

        /**
         * @brief Construct a new Server Launcher object
         */
        ServerLauncher(std::string const &executable_name);

        /**
         * @brief Destroy the Server Launcher object
         */
        ~ServerLauncher();

        /**
         * @brief Launch a UDP server
         * @param port the port of the server
         * @param gameName the name of the game
         */
        void LaunchUdpServer(std::string const &port, std::string const &gameName);

        /**
         * @brief Launch a TCP server
         * @param port the port of the server
         */
        void LaunchTcpServer(std::string const &port);

    private:
        std::string _executable_name;
};

#endif /* !SERVER_LAUNCHER_HPP_ */
