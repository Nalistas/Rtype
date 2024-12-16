/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** AudioDevice
*/

#include "Raylib/AudioDevice.hpp"
#include "raylib.h"

raylib::AudioDevice::AudioDevice()
{
    InitAudioDevice();
}

raylib::AudioDevice::~AudioDevice()
{
    CloseAudioDevice();
}
