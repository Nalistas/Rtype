/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RType
*/

#include "IGame.hpp"
#include <unordered_map>

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class RType : public rtype::IGame {
    public:
        RType();
        ~RType() override;

        void initGameRegistry(std::shared_ptr<ecs::registry> &reg) override;

        std::vector<rtype::ClientAction> getClientActionHandlers(void) const override;

        std::vector<rtype::Background> getBackgrounds(void) const override;

        std::vector<rtype::Sprite> getSprites(void) const override;

        std::vector<std::string> getMusics(void) const override;

        void setUpdateSpeed(SpeedUpdater const &func) override;

        void setUpdatePosition(PositionUpdater const &func) override;

        void setCreate(Creater const &func) override;

        void setDelete(Deleter const &func) override;

        void setUseBackground(BackgroundChanger const &func) override;

        void setUseMusic(MusicChanger const &func) override;

        std::size_t createPlayer(void) override;

        void deletePlayer(std::size_t player_id) override;

        ScreenUpdater getScreenUpdater(void) override;

        std::string getName(void) const override;

    private:
        SpeedUpdater _speedUpdater;
        PositionUpdater _positionUpdater;
        Creater _creater;
        Deleter _deleter;
        BackgroundChanger _backgroundChanger;
        MusicChanger _musicChanger;
        ScreenUpdater _screenUpdater;

        std::unordered_map<std::size_t, ecs::entity> _players;
        std::shared_ptr<ecs::registry> _registry;
};

#endif /* !RTYPE_HPP_ */
