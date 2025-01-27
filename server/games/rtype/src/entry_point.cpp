
#include "registry.hpp"
#include "sparse_array.hpp"
#include "IGame.hpp"
#include "RType.hpp"
#include <memory>


extern "C" {
    std::unique_ptr<rtype::IGame> entry_point()
    {
        return std::make_unique<RType>();
    }
}