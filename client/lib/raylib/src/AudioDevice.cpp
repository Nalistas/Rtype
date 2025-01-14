/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** AudioDevice
*/

#include "AudioDevice.hpp"
#include "raylib.h"

raylib::AudioDevice::AudioDevice()
{
    InitAudioDevice();
}

raylib::AudioDevice::~AudioDevice()
{
    CloseAudioDevice();
}
