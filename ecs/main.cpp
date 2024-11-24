#include "registry.hpp"
#include <iostream>
#include <string>

struct a_s {
    int a;
    std::string b;
    a_s(int a, std::string const &b) : a(a), b(b) {}
    ~a_s() {}
};

int main() {
    registry reg;
    entity e = reg.create_entity();
    reg.register_component<int>();
    reg.emplace_component<int>(e, 42);

    reg.register_component<std::string>();
    reg.emplace_component<std::string>(e, "Hello, World!");

    reg.register_component<a_s>();
    reg.emplace_component<a_s>(e, 42, "Hello, World!");
    reg.delete_entity(e);

    return 0;
}
