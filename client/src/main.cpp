/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include "UdpClient.hpp"
#include "TcpClient.hpp"
#include "Core.hpp"
#include "Login.hpp"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * x)
#else
    #include <unistd.h>
#endif

int main() {
    std::string ip = "127.0.0.1";
    std::string port = "2000";
    std::string username = "Player1";
    bool asBeenConnected = false;

    while (!asBeenConnected) {
        // {
        //     Login login;
        //     if (login.run() == true) {
        //         return 0;
        //     }
        //     ip = login.get_ip();
        //     port = login.get_port();
        //     username = login.get_username();
        // }
        // if (std::count(ip.begin(), ip.end(), '.') != 3) {
        //     std::cerr << "Invalid IP address" << std::endl;
        //     continue;
        // }
        try {
            Core core(ip, port, username);
            core.run();
            asBeenConnected = true;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
