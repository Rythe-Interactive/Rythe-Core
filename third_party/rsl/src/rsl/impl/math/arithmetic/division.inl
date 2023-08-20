#include "division.hpp"
#pragma once
#include <immintrin.h>

#include "division_quaternion.inl"
#include "division_vector.inl"

namespace rsl::math
{
#pragma region Vector
    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool>>
    [[nodiscard]] constexpr auto div(const vec_type0& a, const vec_type1& b) noexcept
    {
        return detail::compute_division<vector<typename vec_type0::scalar, vec_type0::size>>::compute(a, b);
    }

    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool>>
    [[nodiscard]] constexpr auto operator/(const vec_type0& a, const vec_type1& b) noexcept
    {
        return div(a, b);
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool>>
    [[nodiscard]] constexpr auto div(const vec_type& a, typename vec_type::scalar b) noexcept
    {
        return detail::compute_division<vector<typename vec_type::scalar, vec_type::size>>::compute(a, b);
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool>>
    [[nodiscard]] constexpr auto operator/(const vec_type& a, typename vec_type::scalar b) noexcept
    {
        return div(a, b);
    }

    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool>>
    constexpr vec_type0& div_assign(vec_type0& a, const vec_type1& b) noexcept
    {
        return a = detail::compute_division<vector<typename vec_type0::scalar, vec_type0::size>>::compute(a, b);
    }

    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool>>
    constexpr vec_type0& operator/=(vec_type0& a, const vec_type1& b) noexcept
    {
        return div_assign(a, b);
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool>>
    constexpr vec_type& div_assign(vec_type& a, typename vec_type::scalar b) noexcept
    {
        return a = detail::compute_division<vector<typename vec_type::scalar, vec_type::size>>::compute(a, b);
    }

    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool>>
    constexpr vec_type& operator/=(vec_type& a, typename vec_type::scalar b) noexcept
    {
        return div_assign(a, b);
    }
#pragma endregion

#pragma region Quaternion
    //div quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool>>
    [[nodiscard]] constexpr auto div(const quat_type0& a, const quat_type1& b) noexcept
    {
        return detail::compute_division<quaternion<typename quat_type0::scalar>>::compute(a, b);
    }

    //operator /  quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool>>
    [[nodiscard]] constexpr auto operator/(const quat_type0& a, const quat_type1& b) noexcept
    {
        return div(a, b);
    }

    //div quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool>>
    [[nodiscard]] constexpr auto div(const quat_type& a, typename quat_type::scalar b) noexcept
    {
        return detail::compute_division<quaternion<typename quat_type::scalar>>::compute(a, b);
    }

    //operator /  quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool>>
    [[nodiscard]] constexpr auto operator/(const quat_type& a, typename quat_type::scalar b) noexcept
    {
        return div(a, b);
    }


    //div_assign quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool>>
    constexpr quat_type0& div_assign(quat_type0& a, const quat_type1& b) noexcept
    {
        return a = detail::compute_division<quaternion<typename quat_type0::scalar>>::compute(a, b);
    }

    //operator /=  quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool>>
    constexpr quat_type0& operator/=(quat_type0& a, const quat_type1& b) noexcept
    {
        return div_assign(a, b);
    }

    //div_assign quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool>>
    constexpr quat_type& div_assign(quat_type& a, typename quat_type::scalar b) noexcept
    {
        return a = detail::compute_division<quaternion<typename quat_type::scalar>>::compute(a, b);
    }

    //operator /=  quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool>>
    constexpr quat_type& operator/=(quat_type& a, typename quat_type::scalar b) noexcept
    {
        return div_assign(a, b);
    }
#pragma endregion
}
