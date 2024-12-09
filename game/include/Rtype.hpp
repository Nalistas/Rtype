/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "IGame.hpp"
#include "IDisplay.hpp"

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class Rtype : public rtype::IGame {
    public:
        Rtype();
        ~Rtype();

        std::string getName(void) override;

        void setRegistry(ecs::registry &reg) override;

        void processClientAction(ecs::registry &reg, std::string const &action, int client) override;
};

class RtypeGraphics : public rtype::IDisplay {
    public:

        /**
         * @brief Get the name of the display
         * @return the name of the display
         */
        std::string getName() override;

        /**
         * @brief Get the inputs default map
         * @return the inputs default map
         */
        std::map<int, std::string> getInputsDefaultMap() override;

        /**
         * @brief Get the actions
         * @return the actions
         */
        std::list<std::string> getActions() override;

        /**
         * @brief Get the graphical elements
         * @return the graphical elements
         */
        std::map<int, rtype::GraphicalElementData> getGraphicalElements() override;

        /**
         * @brief Get the systems
         * @return the systems
         */
        std::list<std::unique_ptr<ecs::isystem>> getSystems() override;
};

#endif /* !RTYPE_HPP_ */
