/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

#include "Window.hpp"
#include "TextureManager.hpp"
#include "RayText.hpp"

#include <list>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>


Core::Core(std::string ip, std::string port, std::string username) : 
    _window(800, 600),
    _tcpClient(ip, port),
    _roomId(0),
    _startGame(false)
{
    _buttons_room.emplace(
        raylib::RayText("Exit room", 10, 10, 20, raylib::BLUE),
        [&]() { manageExitRoom(); }
    );

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
    _instructions[LEAVE_ENTER_ROOM] = [this](std::vector<uint8_t> tcpResponse) {
        leaveEnterRoom(tcpResponse);
    };
    _instructions[DECLARE_GAME] = [this](std::vector<uint8_t> tcpResponse) {
        std::string gameName(tcpResponse.begin() + 1, tcpResponse.end());

        auto it = std::find(_gameList.begin(), _gameList.end(), gameName);
        if (it == _gameList.end()) {
            _gameList.push_back(gameName);
        }
    };
    _instructions[START_GAME] = [this](std::vector<uint8_t> tcpResponse) {
        (void)tcpResponse;
        _startGame = true;
    };
    _instructions[LOAD_SPRITE] = [this](std::vector<uint8_t> tcpResponse) {
        load_sprite(tcpResponse);
    };
    _instructions[LOAD_MUSIC] = [this](std::vector<uint8_t> tcpResponse) {
        load_music(tcpResponse);
    };
    _instructions[LOAD_BACKGROUND] = [this](std::vector<uint8_t> tcpResponse) {
        load_background(tcpResponse);
    };
    _instructions[LOAD_ACTION] = [this](std::vector<uint8_t> tcpResponse) {
        load_action(tcpResponse);
    };
}

Core::~Core()
{
}

void Core::load_background(std::vector<uint8_t> tcpResponse)
{
    // 4[Speed] [Direction (x = 1, y = 2)] [s'il faut resize (0/1)] [si le background se répete (0/1)] [Type de mouvement (1 : None, 2 : Parallax, 3 : deplacement continue)] [Path to image]
    float speed = *(float *)(tcpResponse.data() + 1);
    int direction = tcpResponse[5];
    bool resize = tcpResponse[6];
    bool repeat = tcpResponse[7];
    int moveType = tcpResponse[8];
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 9));
    // auto texture = raylib::TextureManager::getTexture(path);
    Background background(path, _window.get_size().first, _window.get_size().second);
    _backgrounds.push_back(background);

    checkIfFileExist(path);
}

void Core::load_music(std::vector<uint8_t> tcpResponse)
{
    // 5[id musique][path to musique]
    int id = tcpResponse[1];
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 1));
    raylib::RayMusic music(path);

    checkIfFileExist(path);
}

void Core::load_action(std::vector<uint8_t> tcpResponse)
{
    // 6[id action / 4o][key code / 4o][pressed 1 | released 0]
    uint32_t id = *(uint32_t *)(tcpResponse.data() + 1);
    uint32_t key = *(uint32_t *)(tcpResponse.data() + 5);
    uint8_t pressed = tcpResponse[9];
    // _actions.push_back({pressed, key}); ??? j'ai oublié comment marchait l'ancien client Ambroise
    // MDR, je regarde
    // _actions[pressed].emplace(key, /* function that send the action */);
    // le std::function<void(void)> est la fonctioin qui envoie au serveur udp : 
    // {1, id (sur 4 octets), mouseX (sur 4 octets), mouseY (sur 4 octets)}
    // ou tu remplace :
    // std::array<std::map<uint32_t, std::function<void(void)>>, 2> _actions;
    // par
    // std::array<std::map<uint32_t, uint32_t>, 2> _actions;
}

void Core::checkIfFileExist(std::string path)
{
    if (!std::filesystem::exists("client/" + path)) {
        std::string tcpMessage = std::string(1, MISSING_FILE) + path;
        _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
        // je le recupere comment ???? Ambroise
        // essaye de l'ouvrir !
    }
}

void Core::load_sprite(std::vector<uint8_t> tcpResponse)
{
    // 3[id du type de sprite][size x sur 4 octet] [size y sur 4 octet][ width à prendre sur l'image sur 4o] [height à prendre sur l'image sur 4o] [offset x 4 octets] [offset y 4 octets] [ nb frame sur 1 octet ] [ nb milisecond pour les frame / 4o][path]
    int id = tcpResponse[1];
    int sizeX = *(int *)(tcpResponse.data() + 2);
    int sizeY = *(int *)(tcpResponse.data() + 6);
    float width = *(float *)(tcpResponse.data() + 10);
    float height = *(float *)(tcpResponse.data() + 14);
    int offsetX = *(int *)(tcpResponse.data() + 18);
    int offsetY = *(int *)(tcpResponse.data() + 22);
    uint8_t nbFrames = tcpResponse[26];
    int msPerFrame = *(int *)(tcpResponse.data() + 27);
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 31));
    auto texture = raylib::TextureManager::getTexture(path);
    raylib::Sprite sprite;

    sprite.set_texture(texture);
    sprite.set_offset(offsetX, offsetY);
    sprite.set_source_rect({0, 0, width, height});
    sprite.set_destination_rect({0, 0, static_cast<float>(sizeX), static_cast<float>(sizeY)});

    _sprites.push_back(sprite);
    _sprites.back().set_offset(offsetX, offsetY);

    checkIfFileExist(path);
}

void Core::save_image(const std::string &path, const std::vector<char> &buffer) {
    std::ofstream outFile(path, std::ios::binary);
    if (!outFile) {
        return;
    }
    outFile.write(buffer.data(), buffer.size());
}

void Core::leaveEnterRoom(std::vector<uint8_t> tcpResponse)
{
    if (tcpResponse[1] == 0) {
        _rooms[tcpResponse[2]].setNbPlayers(_rooms[tcpResponse[2]].getNbPlayers() + 1);
    } else {
        _rooms[tcpResponse[2]].setNbPlayers(_rooms[tcpResponse[2]].getNbPlayers() - 1);
    }
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
        if (_instructions.find(static_cast<INSTRUCTIONS_SERVER_TO_CLIENT>(tcpResponse[0])) != _instructions.end()) {
            _instructions[static_cast<INSTRUCTIONS_SERVER_TO_CLIENT>(tcpResponse[0])](tcpResponse);
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
    if (_commandQueue.size() > 0 || _startGame) {
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

        if (_roomId == 0) { // Main menu
            displayCreateRoomBtn(roomName, showPopup);

            if (showPopup) {
                drawPopup(showPopup, roomName, "Enter room name: ");
            } else {
                if (!roomName.empty()) {
                    std::string tcpMessage = std::string(1, CREATE_ROOM) + roomName + "\\testGame";
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    roomName = "";
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
        } else { // Room
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
