#pragma once
#include "../../defines.hpp"

#include "../vector/vector.hpp"
#include "../util/type_util.hpp"

namespace rsl::math
{
    template<typename A, typename B>
    [[nodiscard]] r_always_inline constexpr auto min(A&& a, B&& b);

    template<typename A, typename B>
    [[nodiscard]] r_always_inline constexpr auto max(A&& a, B&& b);

    template<typename In, typename Min, typename Max>
    [[nodiscard]] r_always_inline constexpr auto clamp(In&& in, Min&& min, Max&& max);

    template<typename In>
    [[nodiscard]] r_always_inline constexpr auto saturate(In&& in);
}

#include "constraint.inl"
