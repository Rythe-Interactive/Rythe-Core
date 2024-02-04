#pragma once
#include "feature.hpp"

namespace rythe::core
{
	template <feature_set_c FeatureSetT>
	class module
	{
	public:
		using features = FeatureSetT;
	};

	template <typename... ModulesT>
	struct modules
	{
		using type_sequence = rsl::type_sequence<ModulesT...>;
	};
} // namespace rythe::core
