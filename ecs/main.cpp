#include <iostream>
#include "sparse_array.hpp"
#include "Entity.hpp"

int main() {
    // Test de la classe Entity
    Entity e1(1), e2(2);
    std::cout << "Entity 1 ID: " << static_cast<size_t>(e1) << "\n";
    std::cout << "Entity 2 ID: " << static_cast<size_t>(e2) << "\n";

    // Test de la classe sparse_array
    sparse_array<int> sa;

    // Insertion de valeurs
    sa.insert_at(0, 42);
    sa.insert_at(3, 99);
    sa.emplace_at(5, 123);

    // Affichage des valeurs
    for (size_t i = 0; i < sa.size(); ++i) {
        if (sa[i].has_value()) {
            std::cout << "Index " << i << ": " << *sa[i] << "\n";
        } else {
            std::cout << "Index " << i << ": empty\n";
        }
    }

    // Suppression
    sa.erase(3);
    std::cout << "\nAfter erase:\n";
    for (size_t i = 0; i < sa.size(); ++i) {
        if (sa[i].has_value()) {
            std::cout << "Index " << i << ": " << *sa[i] << "\n";
        } else {
            std::cout << "Index " << i << ": empty\n";
        }
    }

    return 0;
}
