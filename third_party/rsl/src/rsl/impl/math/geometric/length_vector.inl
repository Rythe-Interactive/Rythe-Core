#pragma once
#include "length.hpp"

namespace rsl::math::detail
{
    template<typename T>
    struct compute_length;

    template<typename Scalar, size_type Size>
    struct compute_length<vector<Scalar, Size>>
    {
        using vec_type = vector<Scalar, Size>;

        [[nodiscard]] r_always_inline static Scalar compute(const vec_type& v) noexcept
        {
            return ::std::sqrt(dot(v, v));
        }

        [[nodiscard]] r_always_inline constexpr static Scalar compute2(const vec_type& v) noexcept
        {
            return dot(v, v);
        }
    };

    template<typename Scalar>
    struct compute_length<vector<Scalar, 1u>>
    {
        using vec_type = vector<Scalar, 1u>;

        [[nodiscard]] r_always_inline static Scalar compute(Scalar v) noexcept
        {
            return v;
        }

        [[nodiscard]] r_always_inline constexpr static Scalar compute2(Scalar v) noexcept
        {
            return v * v;
        }
    };

    template<typename Scalar, size_type Size, size_type... args>
    struct compute_length<swizzle<Scalar, Size, args...>>
    {
        using swizzle_type = swizzle<Scalar, Size, args...>;
        using vec_type = typename swizzle_type::conv_type;

        [[nodiscard]] r_always_inline static auto compute(const vec_type& v) noexcept
        {
            return compute_length<vec_type>::compute(v);
        }

        [[nodiscard]] r_always_inline static auto compute2(const vec_type& v) noexcept
        {
            return compute_length<vec_type>::compute(v);
        }
    };
}
