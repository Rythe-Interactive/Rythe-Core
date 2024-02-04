#include "core/engine/module.hpp"
#pragma once
#include "core/ecs/registry.hpp"
#include "core/engine/system.hpp"
#include "core/scheduling/scheduling.hpp"

namespace rythe::core
{
	template <rsl::size_type charc>
	inline rythe_always_inline void Module::createProcessChain(const char (&name)[charc]) const
	{
		schd::Scheduler::createProcessChain<charc>(name);
	}


	template <typename SystemType, typename... Args>
	inline void Module::reportSystem(Args&&... args)
	{
		static_assert(std::is_base_of_v<System<SystemType>, SystemType>, "All systems must inherit from System<SystemType>");

		SystemType* system = static_cast<SystemType*>(m_systems.emplace(rsl::make_hash<SystemType>(), std::make_unique<SystemType>(std::forward<Args>(args)...)).first->second.get());

		if constexpr (rsl::has_setup_v<SystemType, void()>)
		{
			m_setupFuncs.push_back<SystemType, &SystemType::setup>(*system);
		}

		if constexpr (rsl::has_shutdown_v<SystemType, void()>)
		{
			m_shutdownFuncs.push_back<SystemType, &SystemType::shutdown>(*system);
		}

		if constexpr (rsl::has_update_v<SystemType, void(rsl::span)>)
		{
			system->template createProcess<&SystemType::update>("Update");
		}
	}

	template <typename component_type, typename... Args>
	inline rythe_always_inline void Module::registerComponentType(Args&&... args)
	{
		ecs::Registry::registerComponentType<component_type>(std::forward<Args>(args)...);
	}
} // namespace rythe::core
