#include "sin.hpp"
#pragma once

#include "sin_vector.inl"
//#include "sin_matrix.inl"
//#include "sin_quaternion.inl"

namespace rsl::math
{
    // sin
    template<typename T>
    [[nodiscard]] r_always_inline auto sin(T&& value) noexcept
    {
        using Type = ::std::remove_cvref_t<T>;

        if constexpr (is_quat_v<Type>)
        {
            return detail::compute_sin<quaternion<typename Type::scalar>>::compute(::std::forward<T>(value));
        }
        if constexpr (is_matrix_v<Type>)
        {
            return detail::compute_sin<matrix<typename Type::scalar, Type::row_count, Type::col_count>>::compute(::std::forward<T>(value));
        }
        if constexpr (is_vector_v<Type>)
        {
            return detail::compute_sin<vector<typename Type::scalar, Type::size>>::compute(::std::forward<T>(value));
        }
        else
        {
            return ::std::sin(::std::forward<T>(value));
        }
    }

    // asin
    template<typename T>
    [[nodiscard]] r_always_inline auto asin(T&& value) noexcept
    {
        using Type = ::std::remove_cvref_t<T>;

        if constexpr (is_quat_v<Type>)
        {
            return detail::compute_sin<quaternion<typename Type::scalar>>::compute_inverse(::std::forward<T>(value));
        }
        if constexpr (is_matrix_v<Type>)
        {
            return detail::compute_sin<matrix<typename Type::scalar, Type::row_count, Type::col_count>>::compute_inverse(::std::forward<T>(value));
        }
        if constexpr (is_vector_v<Type>)
        {
            return detail::compute_sin<vector<typename Type::scalar, Type::size>>::compute_inverse(::std::forward<T>(value));
        }
        else
        {
            return ::std::asin(::std::forward<T>(value));
        }
    }
}
