#include "normalize.hpp"
#pragma once

#include "normalize_vector.inl"
#include "normalize_quaternion.inl"

namespace rsl::math
{
    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool>>
    [[nodiscard]] r_always_inline auto normalize(const vec_type& v) noexcept
    {
        return detail::compute_normalize<make_vector_t<vec_type>>::compute(v);
    }

    template<typename quat_type, ::std::enable_if_t<is_quat_v<quat_type>, bool>>
    [[nodiscard]] r_always_inline auto normalize(const quat_type& v) noexcept
    {
        return detail::compute_normalize<make_quat_t<quat_type>>::compute(v);
    }
}
