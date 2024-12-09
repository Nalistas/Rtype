/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplay
*/

#include <map>
#include <list>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <memory>

#include "Raylib/RayMusic.hpp"
#include "Raylib/RaySound.hpp"
#include "Raylib/Sprite.hpp"
#include "Background.hpp"
#include "ecs/isystem.hpp"

#ifndef IDISPLAY_HPP_
    #define IDISPLAY_HPP_

namespace rtype {

    struct GraphicalElementData {
        union GraphicalElement {
            raylib::RayMusic music;
            raylib::RaySound sound;
            raylib::Sprite sprite;
            Background background;
        } element;
        std::type_index type;
    };


    class IDisplay {
        public:
            /**
             * @brief Destroy the IDisplay object
             */
            virtual ~IDisplay() = default;

            /**
             * @brief Get the name of the display
             * @return the name of the display
             */
            virtual std::string getName() = 0;

            /**
             * @brief Get the inputs default map
             * @return the inputs default map
             */
            virtual std::map<int, std::string> getInputsDefaultMap() = 0;

            /**
             * @brief Get the actions
             * @return the actions
             */
            virtual std::list<std::string> getActions() = 0;

            /**
             * @brief Get the graphical elements
             * @return the graphical elements
             */
            virtual std::map<int, GraphicalElementData> getGraphicalElements() = 0;

            /**
             * @brief Get the systems
             * @return the systems
             */
            virtual std::list<std::unique_ptr<ecs::isystem>> getSystems() = 0;
    };
}

#endif /* !IDISPLAY_HPP_ */
