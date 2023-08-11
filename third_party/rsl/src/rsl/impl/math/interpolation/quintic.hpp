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
    // quintic
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto quintic(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // quintic
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto quintic(ValueType&& value) noexcept;

    // quintic_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto quintic_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // quintic_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto quintic_derivative(ValueType&& value) noexcept;

    // inverse_quintic
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_quintic(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // inverse_quintic
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_quintic(ValueType&& value) noexcept;

    // inverse_quintic_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_quintic_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept;

    // inverse_quintic_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_quintic_derivative(ValueType&& value) noexcept;
}

#include "quintic.inl"
