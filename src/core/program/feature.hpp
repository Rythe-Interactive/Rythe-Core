#pragma once
#include <rsl/concepts>
#include <rsl/type_util>

namespace rythe::core
{
	struct feature
	{
	};

	template <typename T>
	concept feature_c = std::derived_from<T, feature>;

	template <feature_c... Features>
	struct feature_set
	{
		using type_sequence = rsl::type_sequence<Features...>;
	};

	template <typename T>
	concept feature_set_c = rsl::specialization_of<T, feature_set>;

	template <rsl::type_sequence_c>
	struct to_feature_set;

	template <feature_c... Types>
	struct to_feature_set<rsl::type_sequence<Types...>>
	{
		using type = feature_set<Types...>;
	};

	template <rsl::type_sequence_c TypeSeq>
	using to_feature_set_t = typename to_feature_set<TypeSeq>::type;
} // namespace rythe::core
