/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RType
*/

#include "IGame.hpp"

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class RType : public rtype::IGame {
    public:
        RType();
        ~RType();

        void initGameRegistry(ecs::registry &reg) override;

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
    protected:
    private:
};

#endif /* !RTYPE_HPP_ */
