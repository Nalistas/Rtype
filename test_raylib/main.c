#include "raylib.h"

int main() {
    // Initialisation de la fenêtre et du périphérique audio
    InitWindow(800, 600, "Raylib Audio Example");
    InitAudioDevice(); // Nécessaire pour activer l'audio

    // Charger une musique de fond et un effet sonore
    Music music = LoadMusicStream("music.mp3"); // Assurez-vous que le fichier existe
    Sound fx = LoadSound("sound.wav");         // Assurez-vous que le fichier existe

    // Configurer la musique pour qu'elle joue en boucle
    PlayMusicStream(music);

    Texture2D orange = LoadTexture("orange.png");

    float target_width = 800.0f;
    float target_height = 600.0f;

    Rectangle source = {0, 0, (float)orange.width, (float)orange.height};
    Rectangle destination = {0, 0, target_width, target_height};
    Vector2 origin = {0, 0};

    bool running = true;

    while (!WindowShouldClose() && running) {
        // Mise à jour des flux de musique (obligatoire pour la lecture en continu)
        UpdateMusicStream(music);

        // Détection d'entrée utilisateur pour jouer l'effet sonore
        if (IsKeyPressed(KEY_SPACE)) {
            PlaySound(fx); // Joue l'effet sonore
        }

        if (IsKeyPressed(KEY_A)) {
            running = false;
        }
        // Dessin
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexturePro(orange, source, destination, origin, 0, WHITE);
        DrawText("Appuyez sur ESPACE pour jouer un effet sonore !", 150, 250, 20, DARKGRAY);
        DrawText("La musique de fond joue en continu.", 200, 300, 20, GRAY);
        EndDrawing();
    }

    // Libérer les ressources
    UnloadMusicStream(music);
    UnloadSound(fx);

    // Fermer l'audio et la fenêtre
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
