
#include "registry.hpp"
#include "sparse_array.hpp"
#include "IGame.hpp"
#include "RType.hpp"
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


extern "C" {
    std::unique_ptr<rtype::IGame> entry_point()
    {
        return std::make_unique<RType>();
    }
}