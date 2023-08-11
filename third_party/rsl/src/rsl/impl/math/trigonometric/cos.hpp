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
    // cos
    template<typename T>
    [[nodiscard]] r_always_inline auto cos(T&& v) noexcept;

    // acos
    template<typename T>
    [[nodiscard]] r_always_inline auto acos(T&& v) noexcept;
}

#include "cos.inl"
