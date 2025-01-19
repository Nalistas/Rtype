

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
    _startGame(false),
    _udpClient(),
    _graphicsManager(_window) // pas sur
{
    _buttons_room.emplace(
        raylib::RayText("Exit room", 10, 200, 20, raylib::BLUE),
        [&]() { manageExitRoom(); }
    );
    _buttons_room.emplace(
        raylib::RayText("Get ready", 200, 200, 20, raylib::BLUE),
        [&]() { manageGetReady(); }
    );

    std::string tcpMessage = std::string(1, SET_NAME) + username;
    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    _instructions[OK] = [this](std::vector<uint8_t> tcpResponse) {
        std::cout << "OK" << static_cast<int>(tcpResponse[0]) << std::endl;
        if (_commandQueue.size() > 0) {
            _commandQueue.front().second(tcpResponse);
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
        std::cout << "ROOM_UPDATE" << static_cast<int>(tcpResponse[0]) << std::endl;
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
        _startGame = true;
        std::string ip(reinterpret_cast<char*>(tcpResponse.data() + 1));
        int port = *(int *)(tcpResponse.data() + 5);
        _udpClient.setServer(ip, std::to_string(port));
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
    _instructions[FORCE_REGISTER_IN_ROOM] = [this](std::vector<uint8_t> tcpResponse) {
        forceInRoom(tcpResponse);
    };
    _instructions[DECLARE_GAME] = [this](std::vector<uint8_t> tcpResponse) {
        std::string gameName(reinterpret_cast<char*>(tcpResponse.data() + 1));
        std::cout << "Declare game " << gameName << std::endl;
        _gameList.push_back(gameName);
    };
}

Core::~Core()
{
}

void Core::manageGetReady()
{
    std::string tcpMessage = std::string(1, SET_READY) + "";
    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    _commandQueue.push_back(std::make_pair("getReady", [this](std::vector<uint8_t> tcpResponse) {
        (void) tcpResponse;
        _texts_room.push_back(raylib::RayText("Ready, waiting for other players to get ready", 10, 40, 20, raylib::BLACK));
    }));
}

void Core::forceInRoom(std::vector<uint8_t> tcpResponse)
{
    uint8_t roomId = tcpResponse[1];
    std::cout << "Force in room " << static_cast<int>(roomId) << std::endl;
    std::string roomName(reinterpret_cast<char*>(tcpResponse.data() + 2));
    auto it = std::find_if(_rooms.begin(), _rooms.end(), [roomId](const ClientRoom& room) {
        return room.getId() == roomId;
    });

    if (it == _rooms.end()) {
        _rooms.push_back(ClientRoom(roomName, roomId, 1));
        _rooms.back().setGameName("R-Type");
    } else {
        std::cout << "Enter in room" << std::endl;
        it->setNbPlayers(it->getNbPlayers() + 1);
    }
    setRoom(roomId);
}

void Core::load_background(std::vector<uint8_t> tcpResponse)
{
    // 4[id du bg][Speed] [Direction (x = 1, y = 2)] [s'il faut resize (0/1)] [si le background se répete (0/1)] [Type de mouvement (1 : None, 2 : Parallax, 3 : deplacement continue)] [Path to image]
    int id = *(int *)(tcpResponse.data() + 1);
    float speed = *(float *)(tcpResponse.data() + 5);
    int direction = tcpResponse[6];
    bool resize = tcpResponse[7];
    bool repeat = tcpResponse[8];
    int moveType = tcpResponse[9];
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 10));

    Background background(path, _window.get_size().first, _window.get_size().second);
    background.setSpeed(speed);
    background.setMoveType(static_cast<Background::BACKGROUND_MOVE_TYPE>(moveType));
    background.loop(repeat);
    background.resize_x(1, resize);
    background.resize_y(1, resize);
    _backgrounds[id] = background;

    checkIfFileExist(path);
}

void Core::load_music(std::vector<uint8_t> tcpResponse)
{
    // 5[id musique][path to musique]
    int id = *(int *)(tcpResponse.data() + 1);
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 5));
    _musics.emplace(id, raylib::RayMusic(path));

    checkIfFileExist(path);
}

void Core::load_action(std::vector<uint8_t> tcpResponse)
{
    // 6[id action / 4o][key code / 4o][pressed 1 | released 0]
    uint32_t id = *(uint32_t *)(tcpResponse.data() + 1);
    uint32_t key = *(uint32_t *)(tcpResponse.data() + 5);
    uint8_t pressed = tcpResponse[9];
    _actions[pressed][key] = id;
}

void Core::checkIfFileExist(std::string path)
{
    if (!std::filesystem::exists("client/" + path)) {
        std::string tcpMessage = std::string(1, MISSING_FILE) + path;
        _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
        _commandQueue.push_back(std::make_pair("missingFile", [this, path](std::vector<uint8_t> tcpResponse) {
            if (tcpResponse[0] == KO) {
                return;
            }
            save_image(path, std::vector<char>(tcpResponse.begin() + 1, tcpResponse.end()));
        }));
    }
}

void Core::load_sprite(std::vector<uint8_t> tcpResponse)
{
    // 3[id du type de sprite][size x sur 4 octet] [size y sur 4 octet][ width à prendre sur l'image sur 4o] [height à prendre sur l'image sur 4o] [offset x 4 octets] [offset y 4 octets] [ nb frame sur 1 octet ] [ nb milisecond pour les frame / 4o][path]
    int id = *(int *)(tcpResponse.data() + 1);
    int sizeX = *(int *)(tcpResponse.data() + 6);
    int sizeY = *(int *)(tcpResponse.data() + 10);
    float width = *(float *)(tcpResponse.data() + 14);
    float height = *(float *)(tcpResponse.data() + 18);
    int offsetX = *(int *)(tcpResponse.data() + 22);
    int offsetY = *(int *)(tcpResponse.data() + 26);
    uint8_t nbFrames = tcpResponse[27];
    int msPerFrame = *(int *)(tcpResponse.data() + 28);
    std::string path(reinterpret_cast<char*>(tcpResponse.data() + 32));
    auto texture = raylib::TextureManager::getTexture(path);
    raylib::Sprite sprite;

    sprite.set_texture(texture);
    sprite.set_offset(offsetX, offsetY);
    sprite.set_source_rect({0, 0, width, height});
    sprite.set_destination_rect({0, 0, static_cast<float>(sizeX), static_cast<float>(sizeY)});
    sprite.set_offset(offsetX, offsetY);

    _sprites[id] = sprite;

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
    if (tcpResponse.size() > 1) {
        std::cout << "Room update" << static_cast<int>(tcpResponse[1]) << std::endl;
        if (tcpResponse[1] == 1) {
            _rooms.push_back(ClientRoom(std::string(tcpResponse.begin() + 3, tcpResponse.end() - 2), tcpResponse[2], tcpResponse[tcpResponse.size() - 1]));
            _rooms.back().setGameName("R-Type");
            std::cout << "New room" << std::string(tcpResponse.begin() + 3, tcpResponse.end() - 2) << std::endl;
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
        for (auto c : tcpResponse) {
            std::cout << static_cast<int>(c) << " ";
        }
        std::cout << std::endl;
        if (_instructions.find(static_cast<INSTRUCTIONS_SERVER_TO_CLIENT>(tcpResponse[0])) != _instructions.end()) {
            _instructions[static_cast<INSTRUCTIONS_SERVER_TO_CLIENT>(tcpResponse[0])](tcpResponse);
        }
    }
}

void Core::drawPopup(bool &showPopup, std::vector<raylib::RayText> &inputs, int &focus)
{
    _window.draw_rectangle(100, 100, 1000, 400, raylib::RED);
    _window.draw_text("Enter room name: ", 120, 120, 20, raylib::BLACK);
    _window.draw_text("Enter game name: ", 120, 200, 20, raylib::BLACK);
    _window.draw_text("Press enter to validate", 120, 300, 20, raylib::BLACK);
    _window.draw_rectangle(400, 120 + focus * 80, 300, 40, raylib::GRAY);

    _window.draw_text(inputs[0].getText(), 400, 120, 20, raylib::BLACK);
    _window.draw_text(inputs[1].getText(), 400, 200, 20, raylib::BLACK);

    for (size_t i = 0; i < _gameList.size(); ++i) {
        _window.draw_text(_gameList[i], 120, 330 + 20 * i, 20, raylib::BLUE);
    }

    char key = _window.get_char_pressed();
    if (key >= 32 && key <= 125 && inputs[focus].getText().size() < 20) {
        inputs[focus].setText(inputs[focus].getText() + static_cast<char>(key));
    }
    if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_BACKSPACE) && !inputs[focus].getText().empty()) {
        inputs[focus].setText(inputs[focus].getText().substr(0, inputs[focus].getText().size() - 1));
    }
    if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_ENTER) && focus == static_cast<int>(inputs.size() - 1) && !inputs[0].getText().empty() && !inputs[1].getText().empty()) {
        showPopup = false;
    }
    if (_window.is_key(raylib::Window::PRESSED, raylib::KEY_TAB) ||
        _window.is_key(raylib::Window::PRESSED, raylib::KEY_ENTER)) {
        focus = (focus + 1) % inputs.size();
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

void Core::manageExitRoom()
{
    std::string tcpMessage = std::string(1, LEAVE_ROOM) + "";
    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
    _commandQueue.push_back(std::make_pair("exitRoom", [this](std::vector<uint8_t> tcpResponse) { (void) tcpResponse; setRoom(0); }));
}

void Core::setRoom(uint8_t roomId)
{
    _roomId = roomId;
    _texts_room.clear();
    auto it = std::find_if(_rooms.begin(), _rooms.end(), [roomId](const ClientRoom& room) {
        return room.getId() == roomId;
    });
    if (it == _rooms.end()) {
        return;
    }
    _texts_room.push_back(raylib::RayText("Room id: " + std::to_string(_roomId), 10, 10, 20, raylib::BLACK));
    _texts_room.push_back(raylib::RayText("Room name: " + it->getName(), 10, 40, 20, raylib::BLACK));
    _texts_room.push_back(raylib::RayText("Game name: " + it->getGameName(), 10, 70, 20, raylib::BLACK));
    _texts_room.push_back(raylib::RayText("Number of players: " + std::to_string(it->getNbPlayers()), 10, 100, 20, raylib::BLACK));
}

void Core::run(void)
{
    std::vector<raylib::RayText> inputs({
        raylib::RayText("", 150, 10 + 50 * 0, 30, raylib::BLACK),
        raylib::RayText("", 150, 10 + 50 * 1, 30, raylib::BLACK)
    });
    bool showPopup = false;
    int focus = 0; 

    while (_window.is_running()) {
        interpretor();
        _window.start_drawing();
        _window.clear(raylib::WHITE);

        if (_roomId == 0) { // Main menu
            _window.draw_text("Create room", 10, 10, 20, raylib::BLACK);
            if (isEltPressed(10, 10, 100, 20) && !showPopup) {
                showPopup = true;
                inputs[0].setText("");
                inputs[1].setText("");
                std::string tcpMessage = std::string(1, LIST_GAMES);
                _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                _gameList.clear();
            }

            if (showPopup) {
                drawPopup(showPopup, inputs, focus);
            } else {
                if (!inputs[0].getText().empty() && !inputs[1].getText().empty()) {
                    std::string tcpMessage = std::string(1, CREATE_ROOM) + inputs[0].getText() + "\\" + inputs[1].getText();
                    _tcpClient.send(std::vector<uint8_t>(tcpMessage.begin(), tcpMessage.end()));
                    inputs[0].setText("");
                    inputs[1].setText("");
                }
            }

            for (auto &room : _rooms) {
                _window.draw_text(room.getName(), 10, 50 + room.getId() * 20, 20, raylib::BLACK);
                if (isEltPressed(10, 50 + room.getId() * 20, 200, 20)) {
                    std::cout << "Enter room" << static_cast<int>(_roomId) << std::endl;
                    _tcpClient.send(std::vector<uint8_t>({ENTER_ROOM, room.getId()}));
                    _commandQueue.push_back(std::make_pair("enterRoom", [this, room](std::vector<uint8_t> tcpResponse) { (void) tcpResponse; setRoom(room.getId()); }));
                }
            }
        } else { // Room
            _window.draw_rectangle(0, 0, _window.get_size().first, _window.get_size().second, raylib::RED);
            for (auto &text : _texts_room) {
                text.draw();
            }
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
