/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry template implementation
*/

#include <stdexcept>

#ifndef REGISTRY_TPP_
    #define REGISTRY_TPP_

#include "registry.hpp"

namespace ecs {


/////////////////////////////////////////////////////////////
// Handle the components in the registry
/////////////////////////////////////////////////////////////
template <class Component>
sparse_array<Component> &registry::register_component()
{
    std::type_index type = typeid(Component);
    if (this->_components_arrays.find(type) == this->_components_arrays.end()) {
        this->_components_arrays[type] = sparse_array<Component>();
        this->_destructors[type] = [&](registry &reg, entity const &e) { 
            if (auto& optional_component = reg.get_components<Component>()[e]; optional_component.has_value()) {
                optional_component.reset();
            }
        };

    }
    return std::any_cast<sparse_array<Component>&>(this->_components_arrays[type]);
}

template <class Component>
sparse_array<Component>& registry::get_components()
{
    std::type_index type = typeid(Component);

    if (this->_components_arrays.find(type) == this->_components_arrays.end()) {
        std::string error("Component not registered in registry ");
        throw std::runtime_error(error + type.name());
    }
    std::any_cast<sparse_array<Component>&>(this->_components_arrays.at(type));
    return std::any_cast<sparse_array<Component>&>(this->_components_arrays.at(type));
}

template <class Component>
sparse_array<Component> const& registry::get_components() const
{
    std::type_index type = typeid(Component);
    if (this->_components_arrays.find(type) == this->_components_arrays.end()) {
        std::string error("Component not registered in registry ");
        throw std::runtime_error(error + type.name());
    }
    return std::any_cast<sparse_array<Component> const&>(this->_components_arrays.at(type));
}


/////////////////////////////////////////////////////////////
// handle components of an entity
/////////////////////////////////////////////////////////////
template<typename Component, typename ...Params >
typename sparse_array<Component>::reference_type registry::emplace_component(entity const &to, Params &&...p)
{
    auto &components = this->get_components<Component>();
    return components.emplace_at(to, std::forward<Params>(p)...);
}

template<typename Component>
void registry::remove_component(entity const &from)
{
    auto &type = typeid(Component);
    auto &destructor = this->_destructors.at(type);
    destructor(*this, from);
}

template <class... Components, typename Function>
void registry::add_system(Function&& f) {
    _systems.emplace_back([f = std::forward<Function>(f)](registry& reg) {
        f(reg.get_components<Components>()...);
    });
}


}

#endif /* !REGISTRY_TPP_ */
