#include "lerp.hpp"
#pragma once

namespace rsl::math::detail
{
    template<typename V, typename T>
    [[nodiscard]] r_always_inline constexpr auto _lerp_impl_(V&& a, V&& b, T&& t) noexcept
    {
        return a + (b - a) * t;
    }
}

#include "lerp_vector.inl"
//#include "lerp_matrix.inl"
//#include "lerp_quaternion.inl"

namespace rsl::math
{
    // lerp
    template<typename TypeA, typename TypeB, typename InterpType>
    [[nodiscard]] r_always_inline constexpr auto lerp(TypeA&& a, TypeB&& b, InterpType&& t) noexcept
    {
        using A = ::std::remove_cvref_t<TypeA>;
        using B = ::std::remove_cvref_t<TypeB>;

        if constexpr (is_quat_v<A> && is_quat_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            return detail::compute_lerp<quaternion<scalar>>::compute(::std::forward<TypeA>(a), ::std::forward<TypeB>(b), ::std::forward<InterpType>(t));
        }
        else if constexpr (is_matrix_v<A> && is_matrix_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            return detail::compute_lerp<matrix<scalar, A::row_count, A::col_count>>::compute(::std::forward<TypeA>(a), ::std::forward<TypeB>(b), ::std::forward<InterpType>(t));
        }
        else if constexpr (is_vector_v<A> && is_vector_v<B>)
        {
            using scalar = elevated_t<typename A::scalar, typename B::scalar>;
            constexpr size_type size = min(A::size, B::size);
            return detail::compute_lerp<vector<scalar, size>>::compute(::std::forward<TypeA>(a), ::std::forward<TypeB>(b), ::std::forward<InterpType>(t));
        }
        else
        {
            return detail::_lerp_impl_(::std::forward<TypeA>(a), ::std::forward<TypeB>(b), ::std::forward<InterpType>(t));
        }
    }
}
