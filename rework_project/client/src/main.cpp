/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include "UdpClient.hpp"
#include "TcpClient.hpp"
#include "Core.hpp"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * x)
#else
    #include <unistd.h>
#endif

int main() {
    // Core core;
    // core.run();
    try {
    //     // Test du client UDP
    //     std::cout << "Testing UDP Client..." << std::endl;
    //     UdpClient udpClient("127.0.0.1", "12345");
    //     std::string udpMessage = "Hello, UDP Server!";
    //     udpClient.send(std::vector<char>(udpMessage.begin(), udpMessage.end()));

    //     sleep(1);

    //     if (udpClient.hasData()) {
    //         auto udpResponse = udpClient.receive();
    //         std::cout << "UDP Response: " << std::string(udpResponse.begin(), udpResponse.end()) << std::endl;
    //     }

    // Test du client TCP
    std::cout << "\nTesting TCP Client..." << std::endl;
    TcpClient tcpClient("127.0.0.1", "12345");
    // std::string tcpMessage = "Hello, TCP Server!";
    char id = 1;
    std::string name = "satine";
    std::string tcpMessage = std::string(1, id) + name;
    
    tcpClient.send(std::vector<char>(tcpMessage.begin(), tcpMessage.end()));

    //  std::vector<char> tcpMessage;
    // tcpMessage.push_back(id);
    // tcpMessage.insert(tcpMessage.end(), name.begin(), name.end()); 


    sleep(1);

    if (tcpClient.hasData()) {
        auto tcpResponse = tcpClient.receive();
        std::cout << "TCP Response: " << std::string(tcpResponse.begin(), tcpResponse.end()) << std::endl;
    }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
