/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

#include "Window.hpp"
#include "RayText.hpp"

#include <list>
#include <functional>
#include <string>

Core::Core(std::string ip, std::string port, std::string username) : 
    _window(800, 600),
    _tcpClient(ip, port),
    _roomId(0)
{
    _buttons_room.insert({
        raylib::RayText("Exit room", 10, 10, 20, raylib::BLUE),
        [&]() { manageExitRoom(); }
    });
    std::string tcpMessage = std::string(1, SET_NAME) + username;
    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    _instructions[OK] = [this](std::vector<uint8_t> tcpResponse) {
        std::cout << "OK" << static_cast<int>(tcpResponse[0]) << std::endl;
        if (_commandQueue.size() > 0) {
            _commandQueue.front().second();
            _commandQueue.erase(_commandQueue.begin());
        }
    };
    _instructions[KO] = [this](std::vector<uint8_t> tcpResponse) {
        std::cout << "KO" << static_cast<int>(tcpResponse[0]) << std::endl;
        if (_commandQueue.size() > 0) {
            _commandQueue.erase(_commandQueue.begin());
        }
    };
    _instructions[ROOM_UPDATE] = [this](std::vector<uint8_t> tcpResponse) {
        roomUpdate(tcpResponse);
    };
}

Core::~Core()
{
}

void Core::roomUpdate(std::vector<uint8_t> tcpResponse)
{
    if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 1) {
        if (tcpResponse[1] == 0) {
            _rooms.push_back(ClientRoom(std::string(tcpResponse.begin() + 3, tcpResponse.end() - 2), tcpResponse[2], tcpResponse[tcpResponse.size() - 1]));
        } else {
            auto it = std::find_if(_rooms.begin(), _rooms.end(), [&](const ClientRoom& room) {
                return room.getId() == tcpResponse[2];
            });

            if (it != _rooms.end()) {
                _rooms.erase(it);
            }
        }
    }
}

void Core::interpretor()
{
    while (_tcpClient.hasData()) {
        auto tcpResponse = _tcpClient.receive();
        if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 200) {
            std::cout << "OK" << static_cast<int>(tcpResponse[0]) << std::endl;
            if (_commandQueue.size() > 0) {
                _commandQueue.front().second();
                _commandQueue.erase(_commandQueue.begin());
            }
        } else if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 201) {
            std::cout << "KO" << static_cast<int>(tcpResponse[0]) << std::endl;
            if (_commandQueue.size() > 0) {
                _commandQueue.erase(_commandQueue.begin());
            }
        } else {
            std::cout << "TCP Response: " << std::string(tcpResponse.begin(), tcpResponse.end()) << std::endl;
            if (tcpResponse.size() > 0 && static_cast<uint8_t>(tcpResponse[0]) == 1) {
                // separer par des \ pour avoir le nom de la room et le nombre de joueur
                if (tcpResponse[1] == 0) {
                    _rooms.push_back(ClientRoom(std::string(tcpResponse.begin() + 3, tcpResponse.end() - 2), tcpResponse[2], tcpResponse[tcpResponse.size() - 1]));
                } else {
                    auto it = std::find_if(_rooms.begin(), _rooms.end(), [&](const ClientRoom& room) {
                        return room.getId() == tcpResponse[2];
                    });

                    if (it != _rooms.end()) {
                        _rooms.erase(it);
                    }
                }
            }
        }
    }
}

void Core::drawPopup(bool &showPopup, std::string &input, std::string title)
{
    _window.draw_rectangle(100, 100, 300, 200, raylib::RED);
    _window.draw_text(title, 120, 120, 20);
    _window.draw_rectangle(120, 160, 260, 40, raylib::RED);

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
    if (_commandQueue.size() > 0) {
        return false;
    }
    if (_window.is_mouse_button(raylib::Window::PRESSED, 0) && 
        _window.get_mouse_position().x > x && 
        _window.get_mouse_position().x < x + width && 
        _window.get_mouse_position().y > y && 
        _window.get_mouse_position().y < y + height) {
            return true;
        }
    return false;
}

void Core::displayCreateRoomBtn(std::string &roomName, bool &showPopup)
{
    _window.draw_text("Create room", 10, 10, 20);
    if (isEltPressed(10, 10, 100, 20) && !showPopup) {
        showPopup = true;
        roomName = "";
    }
}

void Core::manageExitRoom()
{
    std::string tcpMessage = std::string(1, LEAVE_ROOM) + "";
    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    _commandQueue.push_back(std::make_pair("exitRoom", [this]() { setRoom(0); }));
}

void Core::setRoom(int roomId)
{
    _roomId = roomId;
}

void Core::run(void)
{
    bool showPopup = false;
    std::string roomName = "";

    while (_window.is_running()) {
        interpretor();
        _window.start_drawing();
        _window.clear(raylib::WHITE);

        if (_roomId == 0) {
            displayCreateRoomBtn(roomName, showPopup);

            if (showPopup) {
                drawPopup(showPopup, roomName, "Enter room name: ");
            } else {
                if (!roomName.empty()) {
                    std::string tcpMessage = std::string(1, CREATE_ROOM) + roomName + "\\testGame";
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    roomName = "";
                    // _commandQueue.push_back(std::make_pair("createRoom", [this]() { setRoom(0); }));
                }
            }

            for (auto &room : _rooms) {
                _window.draw_text(room.getName(), 10, 50 + room.getId() * 20, 20);
                if (isEltPressed(10, 50 + room.getId() * 20, 200, 20)) {
                    std::cout << "Enter room" << _roomId << std::endl;
                    std::string tcpMessage = std::string(1, ENTER_ROOM) + std::to_string(room.getId());
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    _commandQueue.push_back(std::make_pair("enterRoom", [this, room]() { setRoom(room.getId()); }));
                }
            }
        } else {
            _window.draw_rectangle(0, 0, _window.get_size().first, _window.get_size().second, raylib::RED);
            _window.draw_text("Room id: " + std::to_string(_roomId), 10, 50, 20);
            for (auto &button : _buttons_room) {
                button.first.draw();
                if (isEltPressed(button.first.getX(), button.first.getY(), button.first.getSize() * button.first.getText().size(), button.first.getSize())) {
                    button.second();
                }
            }
        }

        _window.end_drawing();
    }
}
