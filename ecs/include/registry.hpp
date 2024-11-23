/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry
*/

#include "sparse_array.hpp"
#include <unordered_map>
#include <any>
#include <typeindex>
#include <typeinfo>

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

class registry {
    public :
        template <class Component>
        sparse_array<Component> &register_component();

        template <class Component>
        sparse_array<Component> & get_components();

        template <class Component>
        sparse_array<Component> const &get_components() const;

    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;
};

#include "registry.tpp"

#endif /* !REGISTRY_HPP_ */
