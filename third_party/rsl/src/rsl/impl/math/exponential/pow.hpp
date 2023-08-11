#pragma once
#include <cmath>

#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"

namespace rsl::math
{
    namespace detail
    {
        template<typename Scalar, size_type Size>
        struct compute_pow
        {
            static constexpr size_type size = Size;
            using value_type = vector<Scalar, size>;

            r_always_inline static value_type compute(const value_type& v, const value_type& s) noexcept
            {
                value_type result;
                for (size_type i; i < size; i++)
                    result[i] = ::std::pow(v[i], s[i]);
                return result;
            }

            r_always_inline static value_type compute(const value_type& v, Scalar s) noexcept
            {
                value_type result;
                for (size_type i; i < size; i++)
                    result[i] = ::std::pow(v[i], s);
                return result;
            }

            r_always_inline static value_type compute_squared(const value_type& v) noexcept
            {
                value_type result;
                for (size_type i; i < size; i++)
                    result[i] = v[i] * v[i];
                return result;
            }
        };

        template<typename Scalar>
        struct compute_pow<Scalar, 1u>
        {
            static constexpr size_type size = 1u;
            using value_type = vector<Scalar, size>;

            r_always_inline static Scalar compute(Scalar v, Scalar s) noexcept
            {
                return ::std::pow(v, s);
            }

            r_always_inline static Scalar compute_squared(Scalar s) noexcept
            {
                return s * s;
            }
        };

        template<typename Scalar>
        struct compute_pow<Scalar, 2u>
        {
            static constexpr size_type size = 2u;
            using value_type = vector<Scalar, size>;

            r_always_inline static value_type compute(const value_type& v, const value_type& s) noexcept
            {
                return value_type{ ::std::pow(v[0], s[0]), ::std::pow(v[1], s[1]) };
            }

            r_always_inline static value_type compute(const value_type& v, Scalar s) noexcept
            {
                return value_type{ ::std::pow(v[0], s), ::std::pow(v[1], s) };
            }

            r_always_inline static value_type compute_squared(const value_type& v) noexcept
            {
                return value_type{ v[0] * v[0], v[1] * v[1] };
            }
        };

        template<typename Scalar>
        struct compute_pow<Scalar, 3u>
        {
            static constexpr size_type size = 3u;
            using value_type = vector<Scalar, size>;

            r_always_inline static value_type compute(const value_type& v, const value_type& s) noexcept
            {
                return value_type{ ::std::pow(v[0], s[0]), ::std::pow(v[1], s[1]), ::std::pow(v[2], s[2]) };
            }

            r_always_inline static value_type compute(const value_type& v, Scalar s) noexcept
            {
                return value_type{ ::std::pow(v[0], s), ::std::pow(v[1], s), ::std::pow(v[2], s) };
            }

            r_always_inline static value_type compute_squared(const value_type& v) noexcept
            {
                return value_type{ v[0] * v[0], v[1] * v[1], v[2] * v[2] };
            }
        };

        template<typename Scalar>
        struct compute_pow<Scalar, 4u>
        {
            static constexpr size_type size = 4u;
            using value_type = vector<Scalar, size>;

            r_always_inline static value_type compute(const value_type& v, const value_type& s) noexcept
            {
                return value_type{ ::std::pow(v[0], s[0]), ::std::pow(v[1], s[1]), ::std::pow(v[2], s[2]), ::std::pow(v[3], s[3]) };
            }

            r_always_inline static value_type compute(const value_type& v, Scalar s) noexcept
            {
                return value_type{ ::std::pow(v[0], s), ::std::pow(v[1], s), ::std::pow(v[2], s), ::std::pow(v[3], s) };
            }

            r_always_inline static value_type compute_squared(const value_type& v) noexcept
            {
                return value_type{ v[0] * v[0], v[1] * v[1], v[2] * v[2], v[3] * v[3] };
            }
        };
    }

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    r_always_inline static auto pow(const vec_type& v, typename vec_type::scalar s) noexcept
    {
        return detail::compute_pow<typename vec_type::scalar, vec_type::size>::compute(v, s);
    }

    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool> = true>
    r_always_inline static auto pow(const vec_type0& v, const vec_type1& s) noexcept
    {
        return detail::compute_pow<typename vec_type0::scalar, vec_type0::size>::compute(v, s);
    }

    template<typename Scalar, ::std::enable_if_t<!is_vector_v<::std::remove_cvref_t<Scalar>>, bool> = true>
    r_always_inline static auto pow(Scalar v, Scalar s) noexcept
    {
        return detail::compute_pow<Scalar, 1u>::compute(v, s);
    }

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    r_always_inline static auto squared(const vec_type& v) noexcept
    {
        return detail::compute_pow<typename vec_type::scalar, vec_type::size>::compute_squared(v);
    }

    template<typename Scalar, ::std::enable_if_t<!is_vector_v<::std::remove_cvref_t<Scalar>>, bool> = true>
    r_always_inline static auto squared(Scalar s) noexcept
    {
        return detail::compute_pow<Scalar, 1u>::compute_squared(s);
    }
}
