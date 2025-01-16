/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

#include "raylib.h"
#include "Window.hpp"

#include <list>
#include <functional>
#include <string>

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
            std::cout << "TCP Response: " << std::string(tcpResponse.begin(), tcpResponse.end()) << std::endl;
            if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 1) {
                // separer par des \ pour avoir le nom de la room et le nombre de joueur
                _rooms.push_back(ClientRoom(std::string(tcpResponse.begin() + 3, tcpResponse.end() - 2), tcpResponse[2], tcpResponse[tcpResponse.size() - 1]));
            }
        }
    }
}


void Core::drawPopup(bool &showPopup, std::string &input, std::string title)
{
    _window.draw_rectangle(100, 100, 300, 200);
    _window.draw_text(title, 120, 120, 20);
    _window.draw_rectangle(120, 160, 260, 40);

    _window.draw_text(input, 130, 170, 20);

    int key = _window.get_char_pressed();
    while (key > 0) {
        if (key >= 32 && key <= 125 && input.size() < 20) {
            input += static_cast<char>(key);
        }

        if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_BACKSPACE) && !input.empty()) { // ca marche po
            input.pop_back();
        }
        key = _window.get_char_pressed();
    }

    if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_ENTER)) {
        showPopup = false;
    }
}

bool Core::isEltPressed(int x, int y, int width, int height)
{
    if (_window.is_mouse_button(raylib::Window::PRESSED, 0) && 
        _window.get_mouse_position().x > x && 
        _window.get_mouse_position().x < x + width && 
        _window.get_mouse_position().y > y && 
        _window.get_mouse_position().y < y + height) {
            return true;
        }
    return false;
}

void Core::run(void)
{
    bool showPopup = false;
    std::string roomName = "";
    int roomId = -1;

    while (_window.is_running()) {
        interpretor();
        _window.start_drawing();
        _window.clear({255, 255, 255, 255});

        if (roomId == -1) {
            if (isEltPressed(10, 10, 100, 20) && !showPopup) {
                showPopup = true;
                roomName = "";
            }

            if (showPopup) {
                drawPopup(showPopup, roomName, "Enter room name: ");
            } else {
                if (!roomName.empty()) {
                    std::string tcpMessage = std::string(1, 7) + roomName + "\\testGame";
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    roomName = "";
                    std::string tcpMessage2 = std::string(1, 8) + "";
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage2.begin(), tcpMessage2.end()));
                }
            }

            _window.draw_text("Create room", 10, 10, 20);

            for (auto &room : _rooms) {
                _window.draw_text(room.getName(), 10, 50 + room.getId() * 20, 20);
                if (isEltPressed(10, 50 + room.getId() * 20, 200, 20)) {
                    roomId = room.getId();
                    std::cout << "Enter room" << roomId << std::endl;
                    std::string tcpMessage = std::string(1, 2) + std::to_string(room.getId());
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    // verifier d'abord si le serveur renvoie 200
                }
            }
        } else {
            _window.draw_rectangle(0, 0, _window.get_size().first, _window.get_size().second);
            _window.draw_text("Room id: " + std::to_string(roomId), 10, 50, 20);
            if (isEltPressed(10, 10, 100, 20)) {
                std::string tcpMessage = std::string(1, 4) + "";
                _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                roomId = -1;
            }
            _window.draw_text("Exit room", 10, 10, 20);
        }

        _window.end_drawing();
    }
}
