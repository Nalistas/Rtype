
#include "registry.hpp"
#include "sparse_array.hpp"
#include "IGame.hpp"
#include <memory>

class IGame : public rtype::IGame
{
    public:
        IGame() = default;
        ~IGame() = default;

        std::string getName() const override
        {
            return "rtype";
        }

        void initGameRegistry(ecs::registry &reg) override {}

        std::vector<rtype::ClientAction> getClientActionHandlers(void) const override {
            return std::vector<rtype::ClientAction>();
        }

        std::vector<rtype::Background> getBackgrounds(void) const override {
            return std::vector<rtype::Background>();
        }

        std::vector<rtype::Sprite> getSprites(void) const override {
            return std::vector<rtype::Sprite>({
                { .path = "data/rtype/rtype.png", .size_x = 64, .size_y = 64, .texture_rect_offset_x = 0, .texture_rect_offset_y = 0, .texture_rect_size_x = 64, .texture_rect_size_y = 64, .nb_frames = 1, .ms_per_frame = 0 },
                { .path = "coucou", .size_x = 0x10000000, .size_y = 32, .texture_rect_offset_x = 0, .texture_rect_offset_y = 0, .texture_rect_size_x = 32, .texture_rect_size_y = 32, .nb_frames = 2, .ms_per_frame = 128 }
            });
        }

        std::vector<std::string> getMusics(void) const override {
            return std::vector<std::string>();
        }

        void setUpdateSpeed(SpeedUpdater const &func) override {}

        void setUpdatePosition(PositionUpdater const &func) override {}

        void setCreate(Creater const &func) override {}

        void setDelete(Deleter const &func) override {}

        void setUseBackground(BackgroundChanger const &func) override {}

        void setUseMusic(MusicChanger const &func) override {}

        std::size_t createPlayer(void) override { return 0; }

        void deletePlayer(std::size_t player_id) override {}

        ScreenUpdater getScreenUpdater(void) override { return [](std::size_t client_id) {}; }

    private:

};

extern "C" {
    std::unique_ptr<rtype::IGame> entry_point()
    {
        return std::make_unique<IGame>();
    }
}