#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../matrix/matrix.hpp"
#include "../quaternion/quaternion_base.hpp"
#include "../util/type_util.hpp"
#include "../basic/constraint.hpp"

#include <cmath>

namespace rsl::math
{
    // tan
    template<typename T>
    [[nodiscard]] r_always_inline auto tan(T&& v) noexcept;

    // atan
    template<typename T>
    [[nodiscard]] r_always_inline auto atan(T&& v) noexcept;
}

#include "tan.inl"
