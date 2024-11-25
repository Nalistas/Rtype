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

namespace ecs {

/**
 * @class registry
 * @brief Management of the entities, components and systems
 */
class registry {
    public :

        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        //      Handle the components in the registry
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        /// @name Registering components
        /// @{

        /**
         * @brief Register a component in the registry.
         * @tparam Component 
         * @return The sparse array of the component just registered
        */
        template <class Component>
        sparse_array<Component> &register_component();

        /**
         * @brief Retrieve the sparse array of a registered component
         * @tparam Component 
         * @return the sparse array of the component
        */
        template <class Component>
        sparse_array<Component> &get_components();

        /**
         * @brief Retrieve the sparse array of a registered component but const
         * @tparam Component 
         * @return the sparse array of the component as const
        */
        template <class Component>
        sparse_array<Component> const &get_components() const;

        /// @}
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        //      Handle the entities in the registry
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        /// @name Handling entities
        /// @{

        /**
         * @brief Give a new entity to the registry and return it
         * @note this function will increment the total entity count
         * or take an entity from the unused entities set
         * @return the new entity
        */
        entity create_entity();

        /**
         * @brief Retrieve an entity from its index
         * @param idx the index of the entity
         * @return the entity
        */
        entity entity_from_index(std::size_t idx);

        /**
         * @brief Delete all the components of an entity
         * @param e the entity to delete and add the unused entity to
         * the unused entities set
        */
        void delete_entity(entity const &e);

        /// @}
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        //      Handle the components in the registry
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        /// @name Handling components
        /// @{

        /**
         * @brief add a component to an entity and return it
         * @tparam Component : the component to add
         * @tparam ...Params : the parameters to pass to the constructor of the component
         * @param to : the entity to add the component to
         * @param ...p : the parameters to pass to the constructor of the component
         * @return return the component just added
        */
        template<typename Component, typename ...Params>
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&...p);

        /**
         * @brief remove a component from an entity
         * @tparam Component the component to remove
         * @param from the entity to remove the component from
        */
        template<typename Component>
        void remove_component(entity const &from);

        /// @}
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        //      Handle the systems
        /////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        /// @name Handling systems
        /// @{

        /**
         * @brief add a system to the registry
         * @tparam ...Components the components used by the system
         * @tparam Function the type of the system (inherit from ecs::system)
         * with #import "system.hpp"
         * @param f the system to add
        */
        template<class ...Components, typename Function>
        void add_system(Function &&f);

        /**
         * @brief run all the systems in the registry
        */
        void run_systems () ;

        /// @}

    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;

        /**
         * @brief Handle destruction of components
         */
        using destructor_t = std::function<void(registry &, entity const &)>;
        std::unordered_map<std::type_index, destructor_t> _destructors;

        /**
         * @brief Keep track of unused entities and size of the registry
         */
        std::set<entity> _unused_entities;
        std::size_t _total_entity_count = 0;

        /**
         * @brief Handle the systems
         */
        std::vector<std::function<void(registry &)>> _systems;
};


}

#include "registry.tpp"

#endif /* !REGISTRY_HPP_ */
