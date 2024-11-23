#include "registry.hpp"
#include <iostream>
#include <string>

int main() {
    registry reg;

    // Enregistrer des composants int
    auto& int_components = reg.register_component<int>();
    int_components.insert_at(0, 42);
    int_components.insert_at(1, 100);

    // Accéder aux composants int
    auto& ints = reg.get_components<int>();
    std::cout << "Int at index 0: " << ints[0].value() << "\n";
    std::cout << "Int at index 1: " << ints[1].value() << "\n";

    // Enregistrer des composants std::string
    auto& string_components = reg.register_component<std::string>();
    string_components.insert_at(0, "Hello");
    string_components.insert_at(1, "World");

    // Accéder aux composants std::string
    auto& strings = reg.get_components<std::string>();
    std::cout << "String at index 0: " << strings[0].value() << "\n";
    std::cout << "String at index 1: " << strings[1].value() << "\n";

    return 0;
}
