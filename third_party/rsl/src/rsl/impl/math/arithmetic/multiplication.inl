#include "multiplication.hpp"
#pragma once
#include <immintrin.h>

#include "multiplication_vector.inl"
#include "multiplication_matrix.inl"
#include "multiplication_quaternion.inl"

namespace rsl::math
{
    // mul
    template<typename TypeA, typename TypeB >
    [[nodiscard]] r_always_inline constexpr auto mul(TypeA&& a, TypeB&& b) noexcept
    {
        using A = ::std::remove_cvref_t<TypeA>;
        using B = ::std::remove_cvref_t<TypeB>;

        if constexpr (is_quat_v<A> && is_quat_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            return detail::compute_multiplication<quaternion<scalar>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else if constexpr (is_vector_v<A> && is_quat_v<B>)
        {
            return detail::compute_multiplication<make_quat_t<B>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else if constexpr (is_matrix_v<A> && is_matrix_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            return detail::compute_multiplication<matrix<scalar, A::row_count, A::col_count>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else if constexpr (is_matrix_v<A> && is_vector_v<B>)
        {
            return detail::compute_multiplication<make_matrix_t<A>>::compute(std::forward<TypeB>(b), std::forward<TypeA>(a));
        }
        else if constexpr (is_vector_v<A> && is_matrix_v<B>)
        {
            return detail::compute_multiplication<make_matrix_t<B>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else if constexpr (is_vector_v<A> && is_vector_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            constexpr size_type size = min(A::size, B::size);
            return detail::compute_multiplication<vector<scalar, size>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else if constexpr (is_vector_v<A> || is_vector_v<B>)
        {            
            return detail::compute_multiplication<vector_type_t<A, B>>::compute(std::forward<TypeA>(a), std::forward<TypeB>(b));
        }
        else
        {
            return a * b;
        }
    }

    // operator *
    template<typename TypeA, typename TypeB, std::enable_if_t<is_linear_algebraic_construct_v<TypeA> || is_linear_algebraic_construct_v<TypeB>, bool>>
    [[nodiscard]] r_always_inline constexpr auto operator*(TypeA&& a, TypeB&& b) noexcept
    {
        return mul(std::forward<TypeA>(a), std::forward<TypeB>(b));
    }

    // mul_assign
    template<typename TypeA, typename TypeB>
    r_always_inline constexpr TypeA& mul_assign(TypeA& a, TypeB&& b) noexcept
    {
        return a = a * b;
    }

    // operator *=
    template<typename TypeA, typename TypeB, std::enable_if_t<is_linear_algebraic_construct_v<TypeA> || is_linear_algebraic_construct_v<TypeB>, bool>>
    r_always_inline constexpr TypeA& operator*=(TypeA& a, TypeB&& b) noexcept
    {
        return a = a * b;
    }

}
