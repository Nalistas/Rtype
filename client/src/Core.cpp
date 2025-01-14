/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

Core::Core(): _tcpClient("127.0.0.1", "12345")
{
}

Core::~Core()
{
}

void Core::interpretor()
{
    while (_tcpClient.hasData()) {
        auto tcpResponse = _tcpClient.receive();
        if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 200) {
            std::cout << "OK" << static_cast<int>(tcpResponse[0]) << std::endl;
        } else if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 201) {
            std::cout << "KO" << static_cast<int>(tcpResponse[0]) << std::endl;
        } else {
            std::cout << "TCP static_cast: " << static_cast<uint8_t>(tcpResponse[0]) << std::endl;
            if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 1) {
                _rooms.push_back(ClientRoom(std::string(tcpResponse.begin() + 3, tcpResponse.end() - 1), tcpResponse[2], tcpResponse[tcpResponse.size() - 1]));
            }
            std::cout << "TCP Response: " << std::string(tcpResponse.begin(), tcpResponse.end()) << std::endl;
        }
    }
}

void Core::run(void)
{
    uint8_t id = 1;
    std::string name = "satine";
    std::string tcpMessage = std::string(1, id) + name;

    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));

    std::string tcpMessage3 = std::string(1, 8) + "";
    _tcpClient.send(std::vector<uint8_t>(tcpMessage3.begin(), tcpMessage3.end()));


    while (_window.is_running()) {
        interpretor();
        _window.start_drawing();
        if (_window.is_mouse_button(raylib::Window::PRESSED, 0) && _window.get_mouse_position().x > 10 && _window.get_mouse_position().x < 200 && _window.get_mouse_position().y > 10 && _window.get_mouse_position().y < 30) {
            std::string tcpMessage4 = std::string(1, 7) + "testNewRoom\\testGame";
            _tcpClient.send(std::vector<uint8_t>(tcpMessage4.begin(), tcpMessage4.end()));
            std::string tcpMessage3 = std::string(1, 8) + "";
            _tcpClient.send(std::vector<uint8_t>(tcpMessage3.begin(), tcpMessage3.end()));
        }
        _window.draw_text("Create room", 10, 10, 20);

        for (auto &room : _rooms) {
            _window.draw_text(room.getName(), 10, 50 + room.getId() * 20, 20);
        }

        _window.end_drawing();
    }
}
