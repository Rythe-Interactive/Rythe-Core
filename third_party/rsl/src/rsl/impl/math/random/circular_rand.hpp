#pragma once
#include "linear_rand.hpp"
#include "../constants.hpp"

namespace rsl::math
{
    template<typename Scalar>
    [[nodiscard]] vector<Scalar, 2> circular_rand(Scalar radius) noexcept;

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>&& vec_type::size == 2, bool> = true>
    [[nodiscard]] auto circular_rand(const vec_type& radii) noexcept;
}

#include "circular_rand.inl"
