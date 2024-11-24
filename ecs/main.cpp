#include "registry.hpp"
#include <iostream>
#include <string>

int main() {
    registry reg;
    entity e = reg.create_entity();
    reg.register_component<int>();
    reg.emplace_component<int>(e, 42);


    return 0;
}
