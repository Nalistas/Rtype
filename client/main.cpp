#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include "Core.hpp"

int main()
{
    Core core(800, 600);
    return core.run();
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
