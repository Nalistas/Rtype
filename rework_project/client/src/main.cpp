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
    //     udpClient.send(std::vector<uint8_t>(udpMessage.begin(), udpMessage.end()));

    //     //sleep(1);

        // if (udpClient.hasData()) {
        //     auto udpResponse = udpClient.receive();
        //     std::cout << "UDP Response: " << std::string(udpResponse.begin(), udpResponse.end()) << std::endl;
        // }

    // Test du client TCP
    std::cout << "\nTesting TCP Client..." << std::endl;
    TcpClient tcpClient("127.0.0.1", "12345");
    // std::string tcpMessage = "Hello, TCP Server!";
    uint8_t id = 1;
    std::string name = "satine";
    std::string tcpMessage = std::string(1, id) + name;
    
    tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    //sleep(1);
    //  std::vector<uint8_t> tcpMessage;
    // tcpMessage.push_back(id);
    // tcpMessage.insert(tcpMessage.end(), name.begin(), name.end());

    std::string tcpMessage3 = std::string(1, 7) + "testNewRoom\\testGame";
    
    tcpClient.send(std::vector<uint8_t>(tcpMessage3.begin(), tcpMessage3.end()));
    //sleep(1);

    // std::string tcpMessage4 = std::string(1, 2) + "1";
    
    // tcpClient.send(std::vector<uint8_t>(tcpMessage4.begin(), tcpMessage4.end()));
    // //sleep(1);

    // std::string tcpMessage5 = std::string(1, 4) + "";
    
    // tcpClient.send(std::vector<uint8_t>(tcpMessage5.begin(), tcpMessage5.end()));
    // //sleep(1);


    uint8_t id2 = 9;
    std::string tcpMessage7 = std::string(1, id2) + "\\1";

    tcpClient.send(std::vector<uint8_t>(tcpMessage7.begin(), tcpMessage7.end()));
    sleep(3);

    while (tcpClient.hasData()) {
        auto tcpResponse = tcpClient.receive();
        if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 200) {
            std::cout << "OK" << static_cast<int>(tcpResponse[0]) << std::endl;
        } else if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 201) {
            std::cout << "KO" << static_cast<int>(tcpResponse[0]) << std::endl;
        } else {
            std::cout << "TCP Response: " << std::string(tcpResponse.begin(), tcpResponse.end()) << std::endl;
        }
    }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
