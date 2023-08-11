#include "inverse.hpp"
#pragma once

#include "inverse_vector.inl"
#include "inverse_quat.inl"
#include "inverse_matrix.inl"

namespace rsl::math
{
    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool>>
    [[nodiscard]] r_always_inline auto inverse(const vec_type& v) noexcept
    {
        return detail::compute_inverse<vec_type>::compute(v);
    }

    template<typename quat_type, ::std::enable_if_t<is_quat_v<quat_type>, bool>>
    [[nodiscard]] r_always_inline auto inverse(const quat_type& q) noexcept
    {
        return detail::compute_inverse<quat_type>::compute(q);
    }

    template<typename mat_type, ::std::enable_if_t<is_matrix_v<mat_type>, bool>>
    [[nodiscard]] r_always_inline auto inverse(const mat_type& m) noexcept
    {
        return detail::compute_inverse<mat_type>::compute(m);
    }
}
