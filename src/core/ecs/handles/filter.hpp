#pragma once

#include <rsl/type_util>

#include <core/ecs/containers/component_container.hpp>
#include <core/ecs/containers/component_pool.hpp>
#include <core/ecs/filters/filterregistry.hpp>
#include <core/ecs/handles/entity.hpp>

namespace rythe::core::ecs
{
	template <typename... component_types>
	struct filter
	{
	private:
		static std::tuple<component_container<component_types>...> m_containers;

	public:
		static const rsl::id_type id;

		[[nodiscard]] static entity_set::iterator begin() noexcept;
		[[nodiscard]] static entity_set::iterator end() noexcept;
		[[nodiscard]] static entity_set::reverse_iterator rbegin() noexcept;
		[[nodiscard]] static entity_set::reverse_iterator rend() noexcept;
		[[nodiscard]] static entity_set::reverse_itr_range reverse_range() noexcept;

		[[nodiscard]] static rsl::size_type size() noexcept;
		[[nodiscard]] static bool empty() noexcept;

		[[nodiscard]] static rsl::size_type count(entity val);
		[[nodiscard]] static rsl::size_type contains(entity val);

		[[nodiscard]] static entity_set::iterator find(entity val);

		[[nodiscard]] static entity& at(rsl::size_type index);
		[[nodiscard]] entity& operator[](rsl::size_type index);

		template <typename component_type>
		[[nodiscard]] static component_container<component_type>& get();
	};
} // namespace rythe::core::ecs

#include <core/ecs/handles/filter.inl>
