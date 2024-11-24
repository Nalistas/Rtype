/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry
*/

#include "sparse_array.hpp"
#include "entity.hpp"
#include <unordered_map>
#include <any>
#include <typeindex>
#include <typeinfo>
#include <set>
#include <functional>

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

class registry {
    public :

        /////////////////////////////////////////////////////////////
        // Handle the components in the registry
        /////////////////////////////////////////////////////////////
        template <class Component>
        sparse_array<Component> &register_component();

        template <class Component>
        sparse_array<Component> & get_components();

        template <class Component>
        sparse_array<Component> const &get_components() const;


        /////////////////////////////////////////////////////////////
        // Handle the entities in the registry
        /////////////////////////////////////////////////////////////
        entity create_entity();
        entity entity_from_index(std::size_t idx) ;
        void delete_entity(entity const &e);


        /////////////////////////////////////////////////////////////
        // Handle the components in the registry
        /////////////////////////////////////////////////////////////
        template<typename Component, typename ...Params >
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&...p);

        template<typename Component>
        void remove_component(entity const &from) ;

    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;

        /////////////////////////////////////////////////////////////
        // Handle destruction of components
        /////////////////////////////////////////////////////////////
        using destructor_t = std::function<void(registry &, entity const &)>;
        std::unordered_map<std::type_index, destructor_t> _destructors;

        /////////////////////////////////////////////////////////////
        // Keep track of unused entities and size of the registry
        /////////////////////////////////////////////////////////////
        std::set<entity> _unused_entities;
        std::size_t _total_entity_count = 0;
};

#include "registry.tpp"

#endif /* !REGISTRY_HPP_ */
