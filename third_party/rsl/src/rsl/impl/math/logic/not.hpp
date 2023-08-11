#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"

namespace rsl::math
{
    namespace detail
    {
        template<typename Scalar, size_type Size>
        struct compute_not
        {
            static constexpr size_type size = Size;
            using value_type = vector<Scalar, size>;

            [[nodiscard]] constexpr static vector<bool, size> compute(const value_type& value) noexcept
            {
                vector<bool, size> result;
                for (size_type i = 0; i < size; i++)
                    result[i] = !value[i];
                return result;
            }
        };

        template<typename Scalar>
        struct compute_not<Scalar, 1u>
        {
            static constexpr size_type size = 1u;
            using value_type = vector<Scalar, size>;

            [[nodiscard]] constexpr static bool compute(Scalar value) noexcept
            {
                return !value;
            }
        };
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    [[nodiscard]] constexpr auto not(const vec_type& value) noexcept
    {
        return detail::compute_not<typename vec_type::scalar, vec_type::size>::compute(value);
    }

    template<typename Scalar, std::enable_if_t<!is_vector_v<Scalar>, bool> = true>
    [[nodiscard]] constexpr auto not(Scalar value) noexcept
    {
        return detail::compute_not<Scalar, 1u>::compute(value);
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    [[nodiscard]] constexpr auto operator!(const vec_type& value) noexcept
    {
        return detail::compute_not<typename vec_type::scalar, vec_type::size>::compute(value);
    }
}
