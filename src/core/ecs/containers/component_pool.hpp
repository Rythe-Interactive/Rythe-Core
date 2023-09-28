#pragma once
#include <rsl/type_util>
#include <rsl/primitives>

#include "core/containers/sparse_map.hpp"
#include "core/events/events.hpp"
#include "core/ecs/prototypes/component_prototype.hpp"
#include "core/ecs/containers/component_container.hpp"
#include "core/ecs/handles/entity.hpp"
#include "core/ecs/filters/filterregistry.hpp"

/**
 * @file component_pool.hpp
 */

namespace rythe::core::ecs
{
    /**@struct component_pool_base
     * @brief Common base class of all component pools that allows the use of component pools without knowing a component type at compile-time.
     */
    struct component_pool_base
    {
        /**@brief Increase the capacity of the component pool to a value that's greater or equal to the passed amount. If amount is greater than the current capacity, new storage is allocated, otherwise the function does nothing.
         */
        virtual void reserve(rsl::size_type amount) = 0;

        /**@brief Erases all components from the pool.
         */
        virtual void clear() = 0;

        /**@brief Creates a component attached to a certain entity.
         * @param target Entity ID to create the component for.
         * @return Pointer to the created component.
         */
        virtual void* create_component(entity target) = 0;

         /**@brief Check if a certain entity has the type of component managed by this pool.
          * @param target Entity ID of the entity to check for.
          * @return True if the specified entity is registered with this pool, false if not.
          */
        [[nodiscard]] virtual bool contains(entity target) const = 0;

        /**@brief Fetch the component attached to a certain entity.
         * @param target Entity ID of the entity the component is attached to.
         * @return Pointer to the component.
         */
        [[nodiscard]] virtual void* get_component(entity target) = 0;
        [[nodiscard]] virtual const void* get_component(entity target) const = 0;

        /**@brief Erase a component attached to a certain entity.
         * @param target Entity ID of the entity the component is attached to.
         */
        virtual void destroy_component(entity target) = 0;

        virtual ~component_pool_base() = default;
    };

    /**@struct component_pool
     * @brief Storage container for all components of a certain type.
     * @tparam component_type Type of components to handle and store.
     */
    template<typename component_type>
    struct component_pool : public component_pool_base
    {
        sparse_map<rsl::id_type, component_type> m_components{ 125 };

        /**@brief Increase the capacity of the component pool to a value that's greater or equal to the passed amount. If amount is greater than the current capacity, new storage is allocated, otherwise the function does nothing.
         */
        virtual void reserve(rsl::size_type size);

        /**@brief Erases all components from the pool.
         */
        virtual void clear();

        /**@brief Creates a component attached to a certain entity.
         * @param target Entity ID to create the component for.
         * @return Pointer to the created component.
         */
        virtual void* create_component(entity target);

        template<typename... Args>
        component_type& create_component(entity target, Args&&... args);

         /**@brief Check if a certain entity has the type of component managed by this pool.
          * @param target Entity ID of the entity to check for.
          * @return True if the specified entity is registered with this pool, false if not.
          */
        [[nodiscard]] virtual bool contains(entity target) const;

        /**@brief Fetch the component attached to a certain entity.
         * @param target Entity ID of the entity the component is attached to.
         * @return Pointer to the component.
         */
        [[nodiscard]] virtual void* get_component(entity target);
        [[nodiscard]] virtual const void* get_component(entity target) const;

        /**@brief Erase a component attached to a certain entity.
         * @param target Entity ID of the entity the component is attached to.
         */
        virtual void destroy_component(entity target);

        void fill_container(component_container<component_type>& container, entity_set& entities);
    };
}
