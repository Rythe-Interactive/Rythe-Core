#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../util/type_util.hpp"

namespace rsl::math
{
    namespace detail
    {
        template<typename T>
        struct compute_division;

        template<typename Scalar,size_type Size>
        struct compute_division<vector<Scalar,Size>>
        {
            static constexpr size_type size = Size;
            using value_type = vector<Scalar,Size>;

            [[nodiscard]] constexpr static value_type compute(const value_type& a, const value_type& b) noexcept
            {
                value_type result;
                for (size_type i = 0; i < size; i++)
                    result[i] = a[i] / b[i];
                return result;
            }

            [[nodiscard]] constexpr static value_type compute(const value_type& a, Scalar b) noexcept
            {
                value_type result;
                Scalar inv = static_cast<Scalar>(1) / b;
                for (size_type i = 0; i < size; i++)
                    result[i] = a[i] * inv;
                return result;
            }
        };

        template<typename Scalar>
        struct compute_division<vector<Scalar, 1u>>
        {
            static constexpr size_type size = 1u;
            using value_type = vector<Scalar, size>;

            [[nodiscard]] constexpr static Scalar compute(Scalar a, Scalar b) noexcept
            {
                return a[0] / b;
            }
        };
    }
}
