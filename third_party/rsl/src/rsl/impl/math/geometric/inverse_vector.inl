#pragma once
#include "inverse.hpp"

namespace rsl::math::detail
{
    template<typename T>
    struct compute_inverse;

    template<typename Scalar, size_type Size>
    struct compute_inverse<vector<Scalar, Size>>
    {
        using vec_type = vector<Scalar, Size>;

        [[nodiscard]] r_always_inline static vec_type compute(const vec_type& v) noexcept
        {
            return vec_type::one / v;
        }
    };

    template<typename Scalar>
    struct compute_inverse<vector<Scalar, 1u>>
    {
        using vec_type = vector<Scalar, 1u>;

        [[nodiscard]] r_always_inline static Scalar compute(Scalar v) noexcept
        {
            return static_cast<Scalar>(1) / v;
        }
    };

    template<typename Scalar, size_type Size, size_type... args>
    struct compute_inverse<swizzle<Scalar, Size, args...>>
    {
        using swizzle_type = swizzle<Scalar, Size, args...>;
        using vec_type = typename swizzle_type::conv_type;

        [[nodiscard]] r_always_inline static auto compute(const vec_type& v) noexcept
        {
            return compute_inverse<vec_type>::compute(v);
        }
    };
}
