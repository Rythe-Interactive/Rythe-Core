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
    // sin
    template<typename T>
    [[nodiscard]] r_always_inline auto sin(T&& v) noexcept;

    // asin
    template<typename T>
    [[nodiscard]] r_always_inline auto asin(T&& v) noexcept;
}

#include "sin.inl"
