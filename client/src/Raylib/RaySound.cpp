/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RaySound
*/

#include "Raylib/RaySound.hpp"
#include <stdexcept>

raylib::RaySound::RaySound(std::string const &path)
{
    _sound = LoadSound(path.c_str());
    if (_sound.stream.buffer == nullptr) {
        throw std::runtime_error("Failed to load sound: " + path + " in the constructor,"
        "Maybe the file doesn't exist or the audio device is instantiated, see the AudioDevice class");
    }

}

raylib::RaySound::~RaySound()
{
    UnloadSound(_sound);
}

void raylib::RaySound::play()
{
    printf("play\n");
    PlaySound(_sound);
}

void raylib::RaySound::stop()
{
    StopSound(_sound);
}

void raylib::RaySound::set_volume(float volume)
{
    SetSoundVolume(_sound, volume);
}

void raylib::RaySound::set_source(std::string const &source)
{
    UnloadSound(_sound);
    _sound = LoadSound(source.c_str());
    if (_sound.stream.buffer == nullptr) {
        throw std::runtime_error("Failed to load sound: " + source);
    }
}
