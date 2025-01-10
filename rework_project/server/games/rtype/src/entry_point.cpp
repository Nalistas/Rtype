
#include "registry.hpp"
#include "sparse_array.hpp"
#include "IGame.hpp"

class IGame : public rtype::IGame
{
    public:
        IGame() = default;
        ~IGame() = default;

        std::string getName() override
        {
            return "R-Type";
        }

        void setRegistry(ecs::registry &reg) override {}

        std::vector<rtype::ClientAction> getClientActionHandlers(void) override {
            return std::vector<rtype::ClientAction>();
        }

        
};

extern "C" {
    void *entry_point()
    {
        return new IGame();
    }
}