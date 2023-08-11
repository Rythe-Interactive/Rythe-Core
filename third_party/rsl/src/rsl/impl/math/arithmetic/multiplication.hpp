#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../matrix/matrix.hpp"
#include "../quaternion/quaternion_base.hpp"
#include "../util/type_util.hpp"
#include "../basic/constraint.hpp"

namespace rsl::math
{
    // mul
    template<typename TypeA, typename TypeB>
    [[nodiscard]] r_always_inline constexpr auto mul(TypeA&& a, TypeB&& b) noexcept;

    // operator *
    template<typename TypeA, typename TypeB, std::enable_if_t<is_linear_algebraic_construct_v<TypeA> || is_linear_algebraic_construct_v<TypeB>, bool> = true>
    [[nodiscard]] r_always_inline constexpr auto operator*(TypeA&& a, TypeB&& b) noexcept;

    // mul_assign
    template<typename TypeA, typename TypeB>
    constexpr TypeA& mul_assign(TypeA& a, TypeB&& b) noexcept;

    // operator *=
    template<typename TypeA, typename TypeB, std::enable_if_t<is_linear_algebraic_construct_v<TypeA> || is_linear_algebraic_construct_v<TypeB>, bool> = true>
    constexpr TypeA& operator*=(TypeA& a, TypeB&& b) noexcept;
}

#include "multiplication.inl"
