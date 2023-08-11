#pragma once
#include <cmath>

#include "determinant.hpp"

namespace rsl::math
{
    template<typename mat_type, ::std::enable_if_t<is_matrix_v<mat_type>, bool> = true>
    [[nodiscard]] r_always_inline constexpr auto adjoint(const mat_type& mat) noexcept;
}

#include "adjoint.inl"
