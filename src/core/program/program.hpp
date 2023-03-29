#pragma once
#include "module.hpp"

namespace rythe::core {
    template<typename This, template<typename> typename... ModulesT>
    class Program {
    public:
        using features = to_feature_set_t<rsl::concat_sequence_t<typename ModulesT<This>::features::type_sequence...>>;
    };
}
