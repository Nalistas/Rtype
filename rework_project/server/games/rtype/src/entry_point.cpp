
#include "registry.hpp"
#include "sparse_array.hpp"
#include "IGame.hpp"
#include <memory>

class handler1 : public rtype::IClientActionHandler {
    public:
        handler1() = default;
        ~handler1() = default;

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override
        {
            std::cout << "handler1: " << client << " " << mouse_x << " " << mouse_y << std::endl;
        }
};

class handler2 : public rtype::IClientActionHandler {
    public:
        handler2() = default;
        ~handler2() = default;

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override
        {
            std::cout << "handler2: " << client << " " << mouse_x << " " << mouse_y << std::endl;
        }
};

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
            return std::vector<rtype::ClientAction>({
                { .key = 1, .pressed = true, .handler = std::make_unique<handler1>() },
                { .key = 2, .pressed = true, .handler = std::make_unique<handler2>() }
            });
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