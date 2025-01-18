/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RayMusic
*/

#include <string>

#ifndef RAYMUSIC_HPP_
    #define RAYMUSIC_HPP_

namespace raylib {
    #include "raylib.h"

class RayMusic {
    public:

        /**
         * @brief Construct a new RayMusic object
         * @param path the path to the music file
         */
        RayMusic(std::string const &path);

        /**
         * @brief Destroy the RayMusic object
         */
        ~RayMusic();

        /**
         * @brief Play the music
         */
        void play();

        /**
         * @brief Stop the music
         */
        void stop();

        /**
         * @brief Modify the volume of the music
         * @param volume the volume of the music
         */
        void set_volume(float volume);

        /**
         * @brief Modify the music source
         * @param source the source of the music
         */
        void set_source(std::string const &source);

        /**
         * @brief Check if the music is playing
         * @return true if the music is playing
         */
        bool is_playing() const;

        /**
         * @brief Get the volume of the music
         * @return the volume of the music as a float
         */
        float get_volume() const;

        /**
         * @brief Update the music
         * @return void
         * @note This function must be called every frame due to the raylib API !!!
         *       Raylib does not load the full file at once in the memory. Otherwise
         *       it would overload the memory. Therefore, the music is load part by part
         *       in the memory. This is why this function must be called every frame
         */
        void update();

        // Overload
        bool operator==(const RayMusic &other) const;
        bool operator!=(const RayMusic &other) const;
        bool operator<(const RayMusic &other) const;
        bool operator>(const RayMusic &other) const; 

    private:
        Music _music;
        float _volume;
};

}


#endif /* !RAYMUSIC_HPP_ */
