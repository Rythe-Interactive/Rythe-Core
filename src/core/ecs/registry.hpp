#pragma once
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>

#include <rsl/primitives>
#include <rsl/type_util>
#include <rsl/hash>

#include "core/containers/sparse_map.hpp"
#include "core/containers/hashed_sparse_set.hpp"
#include "core/engine/enginesubsystem.hpp"
#include "core/ecs/containers/component_pool.hpp"
#include "core/ecs/data/component_type.hpp"
#include "core/ecs/handles/entity.hpp"
#include "core/ecs/handles/component.hpp"
#include "core/ecs/data/entity_data.hpp"
#include "core/ecs/prototypes/entity_prototype.hpp"
#include "core/ecs/meta/meta.hpp"

/**
 * @file registry.hpp
 */

namespace rythe::core::ecs
{
    /**@class Registry
     * @brief Manager and owner of all component families and entities.
     */
    class Registry : public EngineSubSystem<Registry>
    {
        AllowPrivateOnInit;
        AllowPrivateOnShutdown;
        SubSystemInstance(Registry);
    private:
        // All miscellaneous data on entities, eg: hierarchy, active, alive.
        std::unordered_map<rsl::id_type, entity_data> m_entities;

        // All recyclable entities that are dead.
        std::queue<rsl::id_type> m_recyclableEntities;

        std::unordered_map<rsl::id_type, std::unique_ptr<component_pool_base>> m_componentFamilies;

        // Keep track of what the next new entity ID should be.
        rsl::id_type m_nextEntityId = world_entity_id + 1; // First entity should have ID 2; 0 is invalid and 1 is world.

        /**@brief The component compositions of all entities.
         */
        std::unordered_map<rsl::id_type, std::unordered_set<rsl::id_type>> m_entityCompositions;

        static component_pool_base* tryEmplaceFamily(rsl::id_type id, std::unique_ptr<component_pool_base>&& ptr);


        static std::unordered_map<rsl::id_type, std::unique_ptr<component_type_base>>& componentTypes();

        R_NODISCARD static rsl::id_type getNextEntityId();

        static void onInit();
        static void onShutdown();

    public:

        /**@brief Creates world entity if it doesn't exist yet and returns it.
         * @note The world entity can also be retrieved using `ecs::world` and
         *       doesn't require a check for whether the world already exists or not.
         * @return World entity.
         */
        R_NODISCARD static entity getWorld();

        /**@brief Manually registers a component type. Allows use of non templated functions for this component type.
         * @note This function generally not necessary to call manually. All templated functions will try to register
         *       an unknown component type before they attempt their operation.
         * @note For a struct to work as a component it needs to be default constructible.
         * @tparam ComponentType Type of struct you with to register as a component.
         */
        template<typename ComponentType, typename... Args>
        static void registerComponentType(Args&&... args);

        /**@brief Manually registers a component type. Allows use of non templated functions for this component type.
         * @note This function generally not necessary to call manually. All templated functions will try to register
         *       an unknown component type before they attempt their operation.
         * @note For a struct to work as a component it needs to be default constructible.
         * @tparam ComponentType Type of struct you with to register as a component.
         */
        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypes, typename... Args>
        static void registerComponentType(Args&&... args);

        /**@brief Get a pointer to the family of a certain component type.
         */
        template<typename ComponentType, typename... Args>
        R_NODISCARD static component_pool<ComponentType>* getFamily(Args&&... args);

        /**@brief Non templated way to get a pointer to the family of a certain component type.
         * @note Will throw an exception if non of the templated functions have been called
         *       before for this component type due to the type not being registered yet.
         * @param typeId Local type hash of the component type.
         */
        R_NODISCARD static component_pool_base* getFamily(rsl::id_type typeId);

        R_NODISCARD static const std::string& getFamilyName(rsl::id_type id);

        /**@brief Gets the container with all the component storage families.
         */
        R_NODISCARD static std::unordered_map<rsl::id_type, std::unique_ptr<component_pool_base>>& getFamilies();

        /**@brief Creates empty entity with the world as its parent.
         */
        R_NODISCARD static entity createEntity();

        R_NODISCARD static entity createEntity(const std::string& name);

        /**@brief Creates empty entity with a specific entity as its parent.
         * @param parent Entity to assign as the parent of the new entity.
         */
        R_NODISCARD static entity createEntity(entity parent);

        R_NODISCARD static entity createEntity(const std::string& name, entity parent);

        /**@brief Destroys an entity and all its components.
         * @param target Entity to destroy.
         * @param recurse Whether to recursively destroy all the child entities as well. True by default.
         */
        static void destroyEntity(entity target, bool recurse = true);
        static void destroyEntity(rsl::id_type target, bool recurse = true);

        /**@brief Checks if an entity exists and is alive.
         * @param target Entity to check.
         * @return True if the entity is valid and alive, false if the entity is dead or non existent.
         */
        R_NODISCARD static bool checkEntity(entity target);
        R_NODISCARD static bool checkEntity(rsl::id_type target);

        /**@brief Gets the component compositions of all entities.
         */
        R_NODISCARD static std::unordered_map<rsl::id_type, std::unordered_set<rsl::id_type>>& entityCompositions();

        /**@brief Gets the entity specific data of all entities.
         */
        R_NODISCARD static std::unordered_map<rsl::id_type, entity_data>& entityData();

        /**@brief Gets the component composition of a specific entity.
         */
        R_NODISCARD static std::unordered_set<rsl::id_type>& entityComposition(entity target);
        R_NODISCARD static std::unordered_set<rsl::id_type>& entityComposition(rsl::id_type target);

        /**@brief Gets the entity specific data of a specific entity.
         */
        R_NODISCARD static entity_data& entityData(rsl::id_type target);
        R_NODISCARD static entity getEntity(rsl::id_type target);

        /**@brief Creates a new component of a certain type for a specific entity.
         * @tparam ComponentType Type of component to create.
         * @param target Entity to create the component for.
         * @return Reference to the created component.
         */
        template<typename ComponentType>
        static component_ref_t<ComponentType> createComponent(entity target);

        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        static component_ref_tuple<ComponentType0, ComponentType1, ComponentTypeN...> createComponent(entity target);

        /**@brief Adds a precreated component of a certain type to a specific entity.
         * @tparam ComponentType Type of component to create.
         * @param target Entity to create the component for.
         * @param value Component value to use.
         * @return Reference to the created component.
         */
        template<typename ComponentType>
        static component_ref_t<ComponentType> createComponent(entity target, ComponentType&& value);
        template<typename ComponentType>
        static component_ref_t<ComponentType> createComponent(entity target, const ComponentType& value);

        template<typename archetype_type, typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        static typename archetype_type::ref_group createComponent(entity target, ComponentType0&& value0, ComponentType1&& value1, ComponentTypeN&&... valueN);

        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        static component_ref_tuple<ComponentType0, ComponentType1, ComponentTypeN...> createComponent(entity target, ComponentType0&& value0, ComponentType1&& value1, ComponentTypeN&&... valueN);
        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        static component_ref_tuple<ComponentType0, ComponentType1, ComponentTypeN...> createComponent(entity target, const ComponentType0& value0, const ComponentType1& value1, const ComponentTypeN&... valueN);

        /**@brief Creates a new component of a certain type for a specific entity.
         * @param typeId Type hash of component type to create.
         * @param target Entity to create the component for.
         * @return Pointer to the created component.
         */
        static void* createComponent(rsl::id_type typeId, entity target);

        /**@brief Destroys a certain component on a specific entity.
         * @tparam ComponentType Type of the component to destroy.
         * @param target Entity to destroy and remove the component from.
         */
        template<typename ComponentType>
        static void destroyComponent(entity target);

        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        static void destroyComponent(entity target);

        /**@brief Destroys a certain component on a specific entity.
         * @param typeId Type hash of component type to destroy.
         * @param target Entity to destroy and remove the component from.
         */
        static void destroyComponent(rsl::id_type typeId, entity target);

        /**@brief Checks if a specific entity has a certain component.
         * @tparam ComponentType Type of the component to check for.
         * @param target Entity to check the component for.
         * @return True if the target has the component, false if not.
         */
        template<typename ComponentType>
        R_NODISCARD static bool hasComponent(entity target);

        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        R_NODISCARD static bool hasComponent(entity target);

        /**@brief Checks if a specific entity has a certain component.
         * @param typeId Type hash of the component type to check for.
         * @param target Entity to check the component for.
         * @return True if the target has the component, false if not.
         */
        R_NODISCARD static bool hasComponent(rsl::id_type typeId, entity target);

        /**@brief Gets a reference to an existing component.
         * @tparam ComponentType Type of the component to fetch.
         * @param target Entity to get the component from.
         * @return Reference to the component.
         */
        template<typename ComponentType>
        R_NODISCARD static component_ref_t<ComponentType> getComponent(entity target);

        template<typename ComponentType0, typename ComponentType1, typename... ComponentTypeN>
        R_NODISCARD static component_ref_tuple<ComponentType0, ComponentType1, ComponentTypeN... > getComponent(entity target);

        /**@brief Gets a pointer to an existing component.
         * @param typeId Type hash of the component to fetch.
         * @param target Entity to get the component from.
         * @return Pointer to the component.
         */
        R_NODISCARD static void* getComponent(rsl::id_type typeId, entity target);
    };

    ReportSubSystem(Registry);

    /**@brief World entity. All entities and scenes are eventually parented to this entity.
     */
    extern entity world;
}

#include <core/ecs/registry.inl>
#include <core/ecs/containers/component_pool.inl>
#include <core/ecs/filters/filterregistry.inl>
#include <core/ecs/handles/entity.inl>
#include <core/ecs/handles/component.inl>
#include <core/ecs/prototypes/entity_prototype.inl>
#include <core/ecs/archetype/archetype.inl>

