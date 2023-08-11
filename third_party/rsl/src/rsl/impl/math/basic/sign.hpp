#pragma once
#include <cmath>
#include <limits>

#include "../../defines.hpp"
#include "../../util/primitives.hpp"
#include "../util/type_util.hpp"

namespace rsl::math
{
    template<typename Scalar>
    [[nodiscard]] r_always_inline constexpr Scalar sign(Scalar val) noexcept
    {
        if constexpr (::std::is_signed_v<Scalar>)
            return static_cast<Scalar>(1);
        else
            return static_cast<Scalar>((static_cast<Scalar>(0) <= val) - (val < static_cast<Scalar>(0)));
    }

    template<typename Scalar>
    [[nodiscard]] r_always_inline constexpr Scalar signum(Scalar val) noexcept
    {
        if constexpr (::std::is_signed_v<Scalar>)
            return static_cast<Scalar>(0) < val;
        else
            return static_cast<Scalar>((static_cast<Scalar>(0) < val) - (val < static_cast<Scalar>(0)));
    }

    namespace detail
    {
        template<typename T>
        struct compute_signum;

        template<typename Scalar, size_type Size>
        struct compute_signum<vector<Scalar, Size>>
        {
            static constexpr size_type size = Size;
            using vec_type = vector<Scalar, size>;

            [[nodiscard]] r_always_inline constexpr static vec_type compute(const vec_type& val) noexcept
            {
                vec_type result;
                for (size_type i = 0; i < size; i++)
                    result[i] = signum(val[i]);
                return result;
            }

            [[nodiscard]] r_always_inline constexpr static vec_type compute_sign(const vec_type& val) noexcept
            {
                vec_type result;
                for (size_type i = 0; i < size; i++)
                    result[i] = sign(val[i]);
                return result;
            }
        };

        template<typename Scalar>
        struct compute_signum<vector<Scalar, 1>>
        {
            static constexpr size_type size = 1;
            using vec_type = vector<Scalar, size>;

            [[nodiscard]] r_always_inline constexpr static Scalar compute(const vec_type& val) noexcept
            {
                return signum(val[0]);
            }

            [[nodiscard]] r_always_inline constexpr static Scalar compute_sign(const vec_type& val) noexcept
            {
                return sign(val[0]);
            }
        };
    }

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>&& vec_type::size != 1, bool> = true>
    [[nodiscard]] r_always_inline constexpr auto sign(const vec_type& val) noexcept
    {
        return detail::compute_signum<make_vector_t<vec_type>>::compute_sign(val);
    }

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>&& vec_type::size != 1, bool> = true>
    [[nodiscard]] r_always_inline constexpr auto signum(const vec_type& val) noexcept
    {
        return detail::compute_signum<make_vector_t<vec_type>>::compute(val);
    }
}
