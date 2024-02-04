#pragma once
#include <rsl/type_util>

#include "core/ecs/containers/component_pool.hpp"

namespace rythe::core::ecs
{
	struct component_type_base
	{
		std::string componentName;
		rsl::id_type typeId;

		NO_DTOR_RULE5(component_type_base);

		virtual ~component_type_base() = default;

		component_type_base(std::string_view name, rsl::id_type id)
			: componentName(name),
			  typeId(id)
		{
		}

		virtual std::unique_ptr<component_pool_base> create_pool() = 0;
	};

	template <typename ComponentType>
	struct component_type : public component_type_base
	{
		component_type()
			: component_type_base(rsl::nameOfType<ComponentType>(), rsl::typeHash<ComponentType>())
		{
		}
		NO_DEF_CTOR_RULE5(component_type);

		virtual std::unique_ptr<component_pool_base> create_pool() override
		{
			return std::make_unique<component_pool<ComponentType>>();
		}
	};
} // namespace rythe::core::ecs
