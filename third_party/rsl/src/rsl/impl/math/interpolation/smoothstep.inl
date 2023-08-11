#include "smoothstep.hpp"
#pragma once

namespace rsl::math::detail
{
    template<typename T>
    [[nodiscard]] r_always_inline constexpr auto _smoothstep_impl_(T&& v) noexcept
    {
        using scalar = ::std::remove_cvref_t<T>;
        return v * v * (static_cast<scalar>(3) - static_cast<scalar>(2) * v);
    }

    template<typename T>
    [[nodiscard]] r_always_inline constexpr auto _smoothstep_derivative_impl_(T&& v) noexcept
    {
        using scalar = ::std::remove_cvref_t<T>;
        return static_cast<scalar>(-6) * (v - static_cast<scalar>(1)) * v;
    }

    template<typename T>
    [[nodiscard]] r_always_inline auto _inverse_smoothstep_impl_(T&& v) noexcept
    {
        using scalar = ::std::remove_cvref_t<T>;
        return static_cast<scalar>(0.5) - sin(asin(static_cast<scalar>(1) - static_cast<scalar>(2) * v) / static_cast<scalar>(3));
    }

    template<typename T>
    [[nodiscard]] r_always_inline auto _inverse_smoothstep_derivative_impl_(T&& v) noexcept
    {
        using scalar = ::std::remove_cvref_t<T>;
        const auto denom = static_cast<scalar>(3) / sqrt(-(v - 1) * v);
        return cos(asin(static_cast<scalar>(2)*v-static_cast<scalar>(1))/static_cast<scalar>(3)) / denom;
    }
}

#include "smoothstep_vector.inl"
//#include "smoothstep_matrix.inl"
//#include "smoothstep_quaternion.inl"

namespace rsl::math
{
    // smoothstep
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept
    {
        using A = ::std::remove_cvref_t<TypeMin>;
        using B = ::std::remove_cvref_t<TypeMax>;
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<A> && is_quat_v<B> && is_quat_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<quaternion<scalar>>::compute(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<A> && is_matrix_v<B> && is_matrix_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<matrix<scalar, A::row_count, A::col_count>>::compute(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<A> && is_vector_v<B> && is_vector_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            constexpr size_type size = min(A::size, min(B::size, T::size));
            return detail::compute_smoothstep<vector<scalar, size>>::compute(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_smoothstep_impl_(saturate(map01(::std::forward<ValueType>(value), ::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax))));
        }
    }

    // smoothstep
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep(ValueType&& value) noexcept
    {
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<T>)
        {
            return detail::compute_smoothstep<quaternion<typename T::scalar>>::compute(::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<T>)
        {
            return detail::compute_smoothstep<matrix<typename T::scalar, T::row_count, T::col_count>>::compute(::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<T>)
        {
            return detail::compute_smoothstep<vector<typename T::scalar, T::size>>::compute(::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_smoothstep_impl_(::std::forward<ValueType>(value));
        }
    }

    // smoothstep_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept
    {
        using A = ::std::remove_cvref_t<TypeMin>;
        using B = ::std::remove_cvref_t<TypeMax>;
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<A> && is_quat_v<B> && is_quat_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<quaternion<scalar>>::compute_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<A> && is_matrix_v<B> && is_matrix_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<matrix<scalar, A::row_count, A::col_count>>::compute_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<A> && is_vector_v<B> && is_vector_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            constexpr size_type size = min(A::size, min(B::size, T::size));
            return detail::compute_smoothstep<vector<scalar, size>>::compute_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_smoothstep_derivative_impl_(saturate(map01(::std::forward<ValueType>(value), ::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax))));
        }
    }

    // smoothstep_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline constexpr auto smoothstep_derivative(ValueType&& value) noexcept
    {
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<T>)
        {
            return detail::compute_smoothstep<quaternion<typename T::scalar>>::compute_derivative(::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<T>)
        {
            return detail::compute_smoothstep<matrix<typename T::scalar, T::row_count, T::col_count>>::compute_derivative(::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<T>)
        {
            return detail::compute_smoothstep<vector<typename T::scalar, T::size>>::compute_derivative(::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_smoothstep_derivative_impl_(::std::forward<ValueType>(value));
        }
    }

    // inverse_smoothstep
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept
    {
        using A = ::std::remove_cvref_t<TypeMin>;
        using B = ::std::remove_cvref_t<TypeMax>;
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<A> && is_quat_v<B> && is_quat_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<quaternion<scalar>>::compute_inverse(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<A> && is_matrix_v<B> && is_matrix_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<matrix<scalar, A::row_count, A::col_count>>::compute_inverse(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<A> && is_vector_v<B> && is_vector_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            constexpr size_type size = min(A::size, min(B::size, T::size));
            return detail::compute_smoothstep<vector<scalar, size>>::compute_inverse(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_inverse_smoothstep_impl_(saturate(map01(::std::forward<ValueType>(value), ::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax))));
        }
    }

    // inverse_smoothstep
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep(ValueType&& value) noexcept
    {
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<T>)
        {
            return detail::compute_smoothstep<quaternion<typename T::scalar>>::compute_inverse(::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<T>)
        {
            return detail::compute_smoothstep<matrix<typename T::scalar, T::row_count, T::col_count>>::compute_inverse(::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<T>)
        {
            return detail::compute_smoothstep<vector<typename T::scalar, T::size>>::compute_inverse(::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_inverse_smoothstep_impl_(::std::forward<ValueType>(value));
        }
    }

    // inverse_smoothstep_derivative
    template<typename TypeMin, typename TypeMax, typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep_derivative(TypeMin&& edgeMin, TypeMax&& edgeMax, ValueType&& value) noexcept
    {
        using A = ::std::remove_cvref_t<TypeMin>;
        using B = ::std::remove_cvref_t<TypeMax>;
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<A> && is_quat_v<B> && is_quat_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<quaternion<scalar>>::compute_inverse_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<A> && is_matrix_v<B> && is_matrix_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            return detail::compute_smoothstep<matrix<scalar, A::row_count, A::col_count>>::compute_inverse_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<A> && is_vector_v<B> && is_vector_v<T>)
        {
            using scalar = elevated_t<typename A::scalar, elevated_t<typename B::scalar, typename T::scalar>>;
            constexpr size_type size = min(A::size, min(B::size, T::size));
            return detail::compute_smoothstep<vector<scalar, size>>::compute_inverse_derivative(::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax), ::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_inverse_smoothstep_derivative_impl_(saturate(map01(::std::forward<ValueType>(value), ::std::forward<TypeMin>(edgeMin), ::std::forward<TypeMax>(edgeMax))));
        }
    }

    // inverse_smoothstep_derivative
    template<typename ValueType>
    [[nodiscard]] r_always_inline auto inverse_smoothstep_derivative(ValueType&& value) noexcept
    {
        using T = ::std::remove_cvref_t<ValueType>;

        if constexpr (is_quat_v<T>)
        {
            return detail::compute_smoothstep<quaternion<typename T::scalar>>::compute_inverse_derivative(::std::forward<ValueType>(value));
        }
        if constexpr (is_matrix_v<T>)
        {
            return detail::compute_smoothstep<matrix<typename T::scalar, T::row_count, T::col_count>>::compute_inverse_derivative(::std::forward<ValueType>(value));
        }
        if constexpr (is_vector_v<T>)
        {
            return detail::compute_smoothstep<vector<typename T::scalar, T::size>>::compute_inverse_derivative(::std::forward<ValueType>(value));
        }
        else
        {
            return detail::_inverse_smoothstep_derivative_impl_(::std::forward<ValueType>(value));
        }
    }
}
