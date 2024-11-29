/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RaySound
*/

#include <string>
#include "raylib.h"

#ifndef RAYSOUND_HPP_
    #define RAYSOUND_HPP_

namespace raylib
{
/**
 * @brief Sound class using raylib
 */
class RaySound {
    public:
        /**
         * @brief Construct a new RaySound object
         * @param path the path to the sound file
         */
        RaySound(std::string const &path);

        /**
         * @brief Destroy the RaySound object
         */
        ~RaySound();

        /**
         * @brief Play the sound
         */
        void play();

        /**
         * @brief Stop the sound
         */
        void stop();

        /**
         * @brief Modify the volume of the sound
         * @param volume the volume of the sound
         */
        void set_volume(float volume);

        /**
         * @brief Modify the sound source
         * @param source the source of the sound
         */
        void set_source(std::string const &source);

    private:
        Sound _sound;
};

}



#endif /* !RAYSOUND_HPP_ */
