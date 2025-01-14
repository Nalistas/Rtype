/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** AudioDevice
*/

#ifndef AUDIODEVICE_HPP_
    #define AUDIODEVICE_HPP_

namespace raylib {

/**
 * @brief AudioDevice. This class is here to automatically instantiate the audio device.
 * The audio need the call of InitAudioDevice and CloseAudioDevice from raylib to work.
 */
class AudioDevice {
    public:
        /**
         * @brief Construct a new Audio Device object, call InitAudioDevice from raylib
         */
        AudioDevice();

        /**
         * @brief Destroy the Audio Device object, call CloseAudioDevice from raylib
         */
        ~AudioDevice();

    protected:
    private:
};

}


#endif /* !AUDIODEVICE_HPP_ */
