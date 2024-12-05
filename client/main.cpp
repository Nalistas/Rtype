#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include "Raylib/Window.hpp"
#include "Raylib/Sprite.hpp"
#include "Client.hpp"
#include "Background.hpp"
#include "GraphicalCore.hpp"
#include "raylib.h"

int main()
{
    GraphicalCore core(800, 600);
    Background background("./orange.png", 800, 600);

    background.loop(true);
    background.setSpeed(1);
    background.resize_y(core.getWindow().get_size().second, true);
    background.setMoveType(Background::MOVE_X);
    background.setParallaxPos([&core](void) { return core.getConstWindow().get_mouse_position(); });

    core.insertBackground(std::move(background));

    while (core.getWindow().is_running()) {
        core.start_draw();
        core.stop_draw();
        if (core.getWindow().is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_SPACE)) {
            core.getWindow().set_fps(10);
        }
    }
}

// int main() {
//     raylib::Window window(800, 600);
//     // raylib::Sprite sprite("./orange.png");

//     // sprite.set_size(50, 50);
//     // sprite.set_position(400, 300);

//     std::string hostname = "";
//     std::string message = "";
//     bool enteringHostname = true;
//     bool connected = false;
//     Client client;

//     while (!WindowShouldClose()) {
//         std::string &s = (enteringHostname) ? hostname : message;

//         char key = window.get_char_pressed();
//         while (key > 0) {
//             s += key;
//             key = window.get_char_pressed();
//         }

//         if (window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_BACKSPACE) && !s.empty()) {
//             s.pop_back();
//         }

//         if (enteringHostname) {
//             if (window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_ENTER)) {
//                 enteringHostname = false;
//                 connected = true;
//                 client.connect(hostname);
//             }
//         } 
//         else if (connected) {
//             if (window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_ENTER)) {
//                 if (!message.empty()) {
//                     client.send_message(message);
//                     message = "";
//                 }
//             }
//             if (client.has_data()) {
//                 std::string data = client.get_data();
//                 std::cout << "Received data: " << data << std::endl;
//             }
//         }

//         window.start_drawing();
//         window.clear();
//         // sprite.draw();

//         if (enteringHostname) {
//             window.draw_text("Entrez le hostname: " + hostname, 10, 10, 20, BLACK);
//         } else if (connected) {
//             window.draw_text("Entrez un message: " + message, 10, 10, 20, BLACK);
//         }

//         window.end_drawing();
//     }

//     return 0;
// }
