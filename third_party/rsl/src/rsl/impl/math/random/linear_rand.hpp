#pragma once
#include "../vector/vector.hpp"
#include "../util/type_util.hpp"

#include "randomnumbergenerator.hpp"

namespace rsl::math
{
    template<typename Scalar>
    [[nodiscard]] Scalar linear_rand(Scalar min, Scalar max) noexcept;

    template<typename vec_type, typename Scalar, ::std::enable_if_t<is_vector_v<vec_type> && vec_type::size != 1, bool> = true>
    [[nodiscard]] vec_type linear_rand(Scalar min, Scalar max) noexcept;

    template<typename vec_type0, typename vec_type1, ::std::enable_if_t<is_vector_v<vec_type0> && is_vector_v<vec_type1> && vec_type0::size == vec_type1::size, bool> = true>
    [[nodiscard]] auto linear_rand(const vec_type0& min, const vec_type1& max) noexcept;
}

#include "linear_rand.inl"
