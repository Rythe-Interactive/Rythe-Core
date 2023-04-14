#pragma once
#include "module.hpp"

namespace rythe::core {
    template<typename... ModulesT>
    class program {
    public:
        using features = to_feature_set_t<rsl::concat_sequence_t<typename ModulesT::features::type_sequence...>>;

        template<feature_c FeatureT>
        static constexpr bool has_feature() {
            return rsl::type_sequence_contains_v<typename features::type_sequence, FeatureT>;
        }
    };
}
