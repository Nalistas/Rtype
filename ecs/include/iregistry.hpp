/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** iregistry
*/

#include "entity.hpp"

#ifndef IREGISTRY_HPP_
    #define IREGISTRY_HPP_


namespace ecs {
/**
 * @brief Interface for the registry, it doesn't have any implementation and only declare the pure virtual functions that has no template
 */
class iregistry {
    public :
        /**
         * @brief Default destructor
         */
        virtual ~iregistry() = default;

        /**
         * @brief Virtual function to create an entity
         */
        virtual entity create_entity() = 0;

        /**
         * @brief Virtual function to get an entity from its index
         */
        virtual entity entity_from_index(size_t index) = 0;

        /**
         * @brief Virtual function to delete an entity
         */
        virtual void delete_entity(entity const &e) = 0;
};
}


#endif /* !IREGISTRY_HPP_ */
