#pragma once
#include <unordered_map>

#include <core/containers/hashed_sparse_set.hpp>
#include <core/engine/engine.hpp>
#include <core/engine/enginesubsystem.hpp>
#include <rsl/primitives>
#include <rsl/type_util>

#include <core/ecs/filters/filter_info.hpp>
#include <core/ecs/handles/entity.hpp>

/**
 * @file filterregistry.hpp
 */

namespace rythe::core::ecs
{
	template <typename... ComponentTypes>
	struct filter;

	/**@class FilterRegistry
	 * @brief Manager and owner of all entity filter related data.
	 */
	class FilterRegistry : public EngineSubSystem<FilterRegistry>
	{
		AllowPrivateOnInit;
		AllowPrivateOnShutdown;
		SubSystemInstance(FilterRegistry);

	public:
		template <typename... ComponentTypes>
		friend struct filter_info;

		template <typename... ComponentTypes>
		friend struct filter;

		/**@brief Message that a certain component was added to an entity. This will update all filters that might be interested in this entity.
		 * @param componentId Id of the component type.
		 * @param target Entity that was changed.
		 */
		static void markComponentAdd(rsl::id_type componentId, entity target);

		/**@brief Message that a certain component was removed from an entity. This will update all filters that might be interested in this entity.
		 * @param componentId Id of the component type.
		 * @param target Entity that was changed.
		 */
		static void markComponentErase(rsl::id_type componentId, entity target);

		/**@brief Message that a certain component was added to an entity. This will update all filters that might be interested in this entity.
		 * @tparam ComponentType Type of component that was added.
		 * @param target Entity that was changed.
		 */
		template <typename ComponentType>
		static void markComponentAdd(entity target);

		/**@brief Message that a certain component was removed from an entity. This will update all filters that might be interested in this entity.
		 * @tparam ComponentType Type of component that was removed.
		 * @param target Entity that was changed.
		 */
		template <typename ComponentType>
		static void markComponentErase(entity target);

		/**@brief Message that a certain entity was destroyed. This will erase the entity from all interested filters.
		 * @param target Entity that was destroyed.
		 */
		static void markEntityDestruction(entity target);

		/**@brief Message that a certain entity was created with components already applied. This will insert the entity to all interested filters.
		 * @param target Entity that was created.
		 */
		static void markEntityFullCreation(entity target);

		/**@brief Fetch the list of entities that apply to a certain filter.
		 * @param filterId Id of the filter.
		 */
		static entity_set& getList(rsl::id_type filterId);

	private:
		static void onInit();
		static void onShutdown();

		static std::unordered_map<rsl::id_type, entity_set>& entityLists();
		static std::vector<std::unique_ptr<filter_info_base>>& filters();

		template <typename ComponentType>
		constexpr static rsl::id_type generateId() noexcept;

		template <typename ComponentType0, typename ComponentType1, typename... ComponentTypes>
		constexpr static rsl::id_type generateId() noexcept;

		template <typename... ComponentTypes>
		static rsl::id_type generateFilterImpl();

		template <typename... ComponentTypes>
		static rsl::id_type generateFilter();
	};

	ReportSubSystem(FilterRegistry);
} // namespace rythe::core::ecs

#include <core/ecs/filters/filter_info.inl>
