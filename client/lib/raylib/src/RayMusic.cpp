/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RayMusic
*/

#include "RayMusic.hpp"
#include <stdexcept>

raylib::RayMusic::RayMusic(std::string const &path) :
    _volume(1.0f)
{
    _music = LoadMusicStream(path.c_str());
    if (_music.stream.buffer == nullptr) {
        throw std::runtime_error("Failed to load music: " + path + " in the constructor,"
        "Maybe the file doesn't exist or the audio device is instantiated, see the AudioDevice class");
    }
    set_volume(_volume);
}

raylib::RayMusic::~RayMusic()
{
    UnloadMusicStream(_music);
}

void raylib::RayMusic::play()
{
    PlayMusicStream(_music);
}

void raylib::RayMusic::stop()
{
    StopMusicStream(_music);
}

void raylib::RayMusic::set_volume(float volume)
{
    SetMusicVolume(_music, volume);
    _volume = volume;
}

void raylib::RayMusic::set_source(std::string const &source)
{
    UnloadMusicStream(_music);
    _music = LoadMusicStream(source.c_str());
    if (_music.stream.buffer == nullptr) {
        throw std::runtime_error("Failed to load music: " + source + " in the setter,"
        "Maybe the file doesn't exist or the audio device is instantiated, see the AudioDevice class");
    }
}

bool raylib::RayMusic::is_playing() const
{
    return IsMusicStreamPlaying(_music);
}

float raylib::RayMusic::get_volume() const
{
    return _volume;
}

void raylib::RayMusic::update()
{
    UpdateMusicStream(_music);
}
