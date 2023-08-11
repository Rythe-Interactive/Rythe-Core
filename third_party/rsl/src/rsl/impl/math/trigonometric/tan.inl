#include "tan.hpp"
#pragma once

#include "tan_vector.inl"
//#include "tan_matrix.inl"
//#include "tan_quaternion.inl"

namespace rsl::math
{
    // tan
    template<typename T>
    [[nodiscard]] r_always_inline auto tan(T&& value) noexcept
    {
        using Type = ::std::remove_cvref_t<T>;

        if constexpr (is_quat_v<Type>)
        {
            return detail::compute_tan<quaternion<typename Type::scalar>>::compute(::std::forward<T>(value));
        }
        if constexpr (is_matrix_v<Type>)
        {
            return detail::compute_tan<matrix<typename Type::scalar, Type::row_count, Type::col_count>>::compute(::std::forward<T>(value));
        }
        if constexpr (is_vector_v<Type>)
        {
            return detail::compute_tan<vector<typename Type::scalar, Type::size>>::compute(::std::forward<T>(value));
        }
        else
        {
            return ::std::tan(::std::forward<T>(value));
        }
    }

    // atan
    template<typename T>
    [[nodiscard]] r_always_inline auto atan(T&& value) noexcept
    {
        using Type = ::std::remove_cvref_t<T>;

        if constexpr (is_quat_v<Type>)
        {
            return detail::compute_tan<quaternion<typename Type::scalar>>::compute_inverse(::std::forward<T>(value));
        }
        if constexpr (is_matrix_v<Type>)
        {
            return detail::compute_tan<matrix<typename Type::scalar, Type::row_count, Type::col_count>>::compute_inverse(::std::forward<T>(value));
        }
        if constexpr (is_vector_v<Type>)
        {
            return detail::compute_tan<vector<typename Type::scalar, Type::size>>::compute_inverse(::std::forward<T>(value));
        }
        else
        {
            return ::std::atan(::std::forward<T>(value));
        }
    }
}
