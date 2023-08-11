#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../matrix/matrix.hpp"
#include "../quaternion/quaternion_base.hpp"
#include "../util/type_util.hpp"
#include "../basic/constraint.hpp"

namespace rsl::math
{
    // lerp
    template<typename TypeA, typename TypeB, typename InterpType>
    [[nodiscard]] r_always_inline constexpr auto lerp(TypeA&& a, TypeB&& b, InterpType&& t) noexcept;
}

#include "lerp.inl"
