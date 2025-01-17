/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ServerLauncher
*/


#ifndef SERVER_LAUNCHER_HPP_
    #define SERVER_LAUNCHER_HPP_

    #include "RoomsCore.hpp"

class ServerLauncher {
    public:

        /**
         * @brief Construct a new Server Launcher object
         */
        ServerLauncher();

        /**
         * @brief Destroy the Server Launcher object
         */
        ~ServerLauncher();

        void LaunchUdpServer(std::string const &port, std::string const &gameName);
        void LaunchTcpServer(std::string const &port);

    private:
};

#endif /* !SERVER_LAUNCHER_HPP_ */
