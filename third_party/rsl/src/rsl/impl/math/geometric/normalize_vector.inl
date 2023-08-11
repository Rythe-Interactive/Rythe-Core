#pragma once
#include "normalize.hpp"

namespace rsl::math::detail
{
    template<typename T>
    struct compute_normalize;

    template<typename Scalar, size_type Size>
    struct compute_normalize<vector<Scalar, Size>>
    {
        using vec_type = vector<Scalar, Size>;

        [[nodiscard]] r_always_inline static vec_type compute(const vec_type& v) noexcept
        {
            return v / length(v);
        }
    };

    template<typename Scalar>
    struct compute_normalize<vector<Scalar, 1u>>
    {
        using vec_type = vector<Scalar, 1u>;

        [[nodiscard]] r_always_inline static Scalar compute([[maybe_unused]] Scalar v) noexcept
        {
            return static_cast<Scalar>(1);
        }
    };
}
