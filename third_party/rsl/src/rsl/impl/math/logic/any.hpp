#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"

namespace rsl::math
{
    namespace detail
    {
        template<typename Scalar, size_type Size>
        struct compute_any
        {
            static constexpr size_type size = Size;
            using value_type = vector<Scalar, size>;

            [[nodiscard]] constexpr static bool compute(const value_type& value) noexcept
            {
                for (size_type i = 0; i < size; i++)
                    if (value[i])
                        return true;
                return false;
            }
        };
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    [[nodiscard]] constexpr bool any(const vec_type& value) noexcept
    {
        return detail::compute_any<typename vec_type::scalar, vec_type::size>::compute(value);
    }
}
