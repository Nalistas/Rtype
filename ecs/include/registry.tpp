/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry template implementation
*/

#ifndef REGISTRY_TPP_
    #define REGISTRY_TPP_

#include "registry.hpp"

template <class Component>
sparse_array<Component>& registry::register_component()
{
    std::type_index type = typeid(Component);
    if (_components_arrays.find(type) == _components_arrays.end()) {
        _components_arrays[type] = sparse_array<Component>();
    }
    return std::any_cast<sparse_array<Component>&>(_components_arrays[type]);
}

template <class Component>
sparse_array<Component>& registry::get_components()
{
    std::type_index type = typeid(Component);
    return std::any_cast<sparse_array<Component>&>(_components_arrays.at(type));
}

template <class Component>
sparse_array<Component> const& registry::get_components() const
{
    std::type_index type = typeid(Component);
    return std::any_cast<sparse_array<Component> const&>(_components_arrays.at(type));
}

#endif /* !REGISTRY_TPP_ */
