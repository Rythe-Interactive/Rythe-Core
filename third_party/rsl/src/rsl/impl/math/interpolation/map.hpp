#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../matrix/matrix.hpp"
#include "../quaternion/quaternion_base.hpp"
#include "../util/type_util.hpp"
#include "../basic/constraint.hpp"

namespace rsl::math
{
    // map
    template<typename T, typename InMin, typename InMax, typename OutMin, typename OutMax>
    [[nodiscard]] r_always_inline constexpr auto map(T&& value, InMin&& inMin, InMax&& inMax, OutMin&& outMin, OutMax&& outMax) noexcept;

    template<typename T, typename InMin, typename InMax>
    [[nodiscard]] r_always_inline constexpr auto map01(T&& value, InMin&& inMin, InMax&& inMax) noexcept;
}

#include "map.inl"
