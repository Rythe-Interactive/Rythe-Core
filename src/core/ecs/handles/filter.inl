#include <core/ecs/handles/filter.hpp>
#pragma once

namespace rythe::core::ecs
{
	template <typename... ComponentTypes>
	const rsl::id_type filter<ComponentTypes...>::id = FilterRegistry::generateFilter<ComponentTypes...>();

	template <typename... ComponentTypes>
	std::tuple<component_container<ComponentTypes>...> filter<ComponentTypes...>::m_containers;

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::iterator filter<ComponentTypes...>::begin() noexcept
	{
		return FilterRegistry::getList(id).begin();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::iterator filter<ComponentTypes...>::end() noexcept
	{
		return FilterRegistry::getList(id).end();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::reverse_iterator filter<ComponentTypes...>::rbegin() noexcept
	{
		return FilterRegistry::getList(id).rbegin();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::reverse_iterator filter<ComponentTypes...>::rend() noexcept
	{
		return FilterRegistry::getList(id).rend();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::reverse_itr_range filter<ComponentTypes...>::reverse_range() noexcept
	{
		return FilterRegistry::getList(id).reverse_range();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline rsl::size_type filter<ComponentTypes...>::size() noexcept
	{
		return FilterRegistry::getList(id).size();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline bool filter<ComponentTypes...>::empty() noexcept
	{
		return FilterRegistry::getList(id).empty();
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline rsl::size_type filter<ComponentTypes...>::count(entity val)
	{
		return FilterRegistry::getList(id).count(val);
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline rsl::size_type filter<ComponentTypes...>::contains(entity val)
	{
		return FilterRegistry::getList(id).contains(val);
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity_set::iterator filter<ComponentTypes...>::find(entity val)
	{
		return FilterRegistry::getList(id).find(val);
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity& filter<ComponentTypes...>::at(rsl::size_type index)
	{
		return FilterRegistry::getList(id).at(index);
	}

	template <typename... ComponentTypes>
	[[nodiscard]] inline rythe_always_inline entity& filter<ComponentTypes...>::operator[](rsl::size_type index)
	{
		return FilterRegistry::getList(id).at(index);
	}

	template <typename... ComponentTypes>
	template <typename ComponentType>
	[[nodiscard]] inline rythe_always_inline component_container<ComponentType>& filter<ComponentTypes...>::get()
	{
		auto& container = std::get<component_container<ComponentType>>(m_containers);
		container.clear();
		reinterpret_cast<component_pool<ComponentType>*>(Registry::getFamily(rsl::typeHash<ComponentType>()))->fill_container(container, FilterRegistry::getList(id));
		return container;
	}
} // namespace rythe::core::ecs
