// #include "raylib.h"
#include <stdio.h>
#include <unistd.h>
#include "Window.hpp"
#include "Sprite.hpp"

int main(void)
{
    raylib::Window window(800, 600);
    raylib::Sprite sprite("sprite.png");

    window.set_fps(10);
    sprite.set_size(50, 50);
    sprite.set_position(400, 300);
    sprite.set_source_rect({30, 150, 70, 150});

    while (window.is_running()) {
        std::list<int> keys = window.get_keys();

        window.start_drawing();
        window.clear();
        sprite.draw();
        window.draw_text("test", 10, 10, 20, BLACK);
        
        unsigned int i = 0;
        for (auto it = keys.begin(); it != keys.end(); it++) {
            window.draw_text(std::to_string(*it), 10, 50 + i * 20, 20, BLACK);
            i++;
        }

        keys = window.get_mouse_buttons();
        i = 0;
        for (auto it = keys.begin(); it != keys.end(); it++) {
            window.draw_text(std::to_string(*it), 100, 50 + i * 20, 20, BLACK);
            i++;
        }
        window.end_drawing();

    }
    return 0;
}

// int main(void) {
//     // Initialisation de la fenêtre
//     InitWindow(800, 600, "Liste des touches pressées");

//     SetTargetFPS(60);

//     // Boucle principale
//     while (!WindowShouldClose()) {
//         // Début du dessin
//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         DrawText("Touches actuellement appuyées :", 10, 10, 20, BLACK);

//         // Parcourir toutes les touches possibles (KEY_SPACE est la plus haute constante connue de Raylib)
//         int y = 40; // Position verticale pour afficher les touches
//         for (int key = 32; key <= 348; key++) { // 32 = espace, 348 = F12 (vous pouvez ajuster cette plage)
//             if (IsKeyDown(key)) {
//                 // Afficher la touche appuyée
//                 DrawText(TextFormat("Key %d is pressed", key), 10, y, 20, BLUE);
//                 y += 20;
//             }
//         }

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }


// #include "raylib.h"

// int main() {
//     // Initialisation de la fenêtre et du périphérique audio
//     InitWindow(800, 600, "Raylib Audio Example");
//     InitAudioDevice(); // Nécessaire pour activer l'audio

//     // Charger une musique de fond et un effet sonore
//     Music music = LoadMusicStream("music.mp3"); // Assurez-vous que le fichier existe
//     Sound fx = LoadSound("sound.wav");         // Assurez-vous que le fichier existe

//     // Configurer la musique pour qu'elle joue en boucle
//     PlayMusicStream(music);

//     Texture2D orange = LoadTexture("orange.png");

//     float target_width = 80.0f;
//     float target_height = 60.0f;

//     Rectangle source = {500, 500, (float)orange.width - 500, (float)orange.height - 500}; // 
//     Rectangle destination = {400, 300, target_width, target_height};
//     Vector2 origin = {40.0f, 30.0f};

//     bool running = true;

//     while (!WindowShouldClose() && running) {
//         // Mise à jour des flux de musique (obligatoire pour la lecture en continu)
//         UpdateMusicStream(music);

//         // Détection d'entrée utilisateur pour jouer l'effet sonore
//         if (IsKeyPressed(KEY_SPACE)) {
//             PlaySound(fx); // Joue l'effet sonore
//         }

//         if (IsKeyPressed(KEY_A)) {
//             running = false;
//         }
//         // Dessin
//         BeginDrawing();

//         ClearBackground(RAYWHITE);
//         DrawTexturePro(orange, source, destination, origin, 90, WHITE);
//         DrawText("Appuyez sur ESPACE pour jouer un effet sonore !", 150, 250, 20, DARKGRAY);
//         DrawText("La musique de fond joue en continu.", 200, 300, 20, GRAY);
//         EndDrawing();
//     }

//     // Libérer les ressources
//     UnloadMusicStream(music);
//     UnloadSound(fx);
//     UnloadTexture(orange);

//     // Fermer l'audio et la fenêtre
//     CloseAudioDevice();
//     CloseWindow();
//     return 0;
// }
