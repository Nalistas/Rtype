/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RType
*/

#include "IGame.hpp"
#include <unordered_map>
#include <unordered_set>

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

/**
 * @brief RType class to handle the game RType
 */
class RType : public rtype::IGame {
    public:
        RType();
        ~RType() override;

        /**
         * @brief Initialize the game registry
         * 
         * @param reg
         */
        void initGameRegistry(std::shared_ptr<ecs::registry> &reg) override;

        /**
         * @brief Get the list of client actions handlers
         * 
         * @return std::vector<rtype::ClientAction>
         */
        std::vector<rtype::ClientAction> getClientActionHandlers(void) const override;


        /**
         * @brief Get the list of backgrounds
         * 
         * @return std::vector<rtype::Background>
         */
        std::vector<rtype::Background> getBackgrounds(void) const override;

        /**
         * @brief Get the list of sprites
         * 
         * @return std::vector<rtype::Sprite>
         */
        std::vector<rtype::Sprite> getSprites(void) const override;


        /**
         * @brief Get the list of musics
         * 
         * @return std::vector<std::string>
         */
        std::vector<std::string> getMusics(void) const override;

        /**
         * @brief Get the list of texts
         * 
         * @return std::vector<rtype::Text>
         */
        std::vector<rtype::Text> getTexts(void) const override;


        /**
         * @brief Set the update speed function
         * 
         * @param func
         */
        void setUpdateSpeed(SpeedUpdater const &func) override;


        /**
         * @brief Set the update position function
         * 
         * @param func
         */
        void setUpdatePosition(PositionUpdater const &func) override;

        /**
         * @brief Set the create function
         * 
         * @param func
         */
        void setCreate(Creater const &func) override;


        /**
         * @brief Set the delete function
         * 
         * @param func
         */
        void setDelete(Deleter const &func) override;


        /**
         * @brief Set the use background function
         * 
         * @param func
         */
        void setUseBackground(BackgroundChanger const &func) override;

        /**
         * @brief Set the use music function
         * 
         * @param func
         */
        void setUseMusic(MusicChanger const &func) override;

        /**
         * @brief Set the update score function
         * 
         * @param func
         */
        void setTextUpdater(TextUpdater const &func) override; 

        /**
         * @brief Create a player
         * 
         * @return std::size_t
         */
        std::size_t createPlayer(void) override;

        /**
         * @brief Delete a player
         */
        void deletePlayer(std::size_t player_id) override;

        /**
         * @brief Get the screen updater
         */
        ScreenUpdater getScreenUpdater(void) override;

        /**
         * @brief Get the name of the game
         * 
         * @return std::string
         */
        std::string getName(void) const override;


    private:
        SpeedUpdater _speedUpdater;
        PositionUpdater _positionUpdater;
        Creater _creater;
        Deleter _deleter;
        BackgroundChanger _backgroundChanger;
        MusicChanger _musicChanger;
        ScreenUpdater _screenUpdater;
        TextUpdater _textUpdater;

        std::unordered_map<std::size_t, std::size_t> _players;
        std::unordered_set<std::size_t> _deadPlayers;
        std::shared_ptr<ecs::registry> _registry;
        int _score;
        bool _lose;
};

#endif /* !RTYPE_HPP_ */
