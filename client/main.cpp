#include <stdio.h>
#include <iostream>
#include <string>
#include "Window.hpp"
#include "Sprite.hpp"
#include "Client.hpp"

int main() {
    raylib::Window window(800, 600);
    raylib::Sprite sprite("./orange.png");

    sprite.set_size(50, 50);
    sprite.set_position(400, 300);

    std::string hostname = "";
    std::string message = "";
    bool enteringHostname = true;
    bool connected = false;
    Client* client = nullptr;

    while (!WindowShouldClose()) {
        if (enteringHostname) {
            int key = GetCharPressed();

            while (key > 0) {
                if (key == KEY_BACKSPACE && !hostname.empty()) {
                    hostname.pop_back();
                } else if (key >= 32 && key <= 126) {
                    hostname += static_cast<char>(key);
                }
                key = GetCharPressed();
            }

            if (IsKeyDown(KEY_BACKSPACE) && !hostname.empty()) {
                hostname.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER)) {
                enteringHostname = false;
                connected = true;
                client = new Client(hostname);
            }
        } 
        else if (connected) {
            int key = GetCharPressed();

            while (key > 0) {
                if (key == KEY_BACKSPACE && !message.empty()) {
                    message.pop_back();
                } else if (key >= 32 && key <= 126) {
                    message += static_cast<char>(key);
                }
                key = GetCharPressed();
            }

            if (IsKeyDown(KEY_BACKSPACE) && !message.empty()) {
                message.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (!message.empty() && client != nullptr) {
                    client->send_message(message);
                    message = "";
                }
            }
        }

        window.start_drawing();
        window.clear();
        sprite.draw();

        if (enteringHostname) {
            window.draw_text("Entrez le hostname: " + hostname, 10, 10, 20, BLACK);
        } else if (connected) {
            window.draw_text("Entrez un message: " + message, 10, 10, 20, BLACK);
        }

        window.end_drawing();
    }

    if (client != nullptr) {
        delete client;
    }

    return 0;
}
