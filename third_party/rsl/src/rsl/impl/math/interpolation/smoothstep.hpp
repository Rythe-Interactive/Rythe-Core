#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../matrix/matrix.hpp"
#include "../quaternion/quaternion_base.hpp"
#include "../util/type_util.hpp"
#include "../basic/constraint.hpp"
#include "../exponential/sqrt.hpp"
#include "map.hpp"
#include "../trigonometric/trigonometric.hpp"

namespace rsl::math
{
    // smoothstep
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // smoothstep
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep(ValueType&& value) noexcept;

    // smoothstep_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // smoothstep_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep_derivative(ValueType&& value) noexcept;

    // inverse_smoothstep
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // inverse_smoothstep
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep(ValueType&& value) noexcept;

    // inverse_smoothstep_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // inverse_smoothstep_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep_derivative(ValueType&& value) noexcept;
}

#include "smoothstep.inl"
