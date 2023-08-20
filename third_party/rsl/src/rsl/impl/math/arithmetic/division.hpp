#pragma once
#include "../../util/primitives.hpp"
#include "../vector/vector.hpp"
#include "../quaternion/quaternion.hpp"
#include "../util/type_util.hpp"

namespace rsl::math
{
#pragma region Vector
    //div vec/vec
    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0> && is_vector_v<vec_type1>, bool> = true>
    [[nodiscard]] constexpr auto div(const vec_type0& a, const vec_type1& b) noexcept;

    //operator /  vec/vec
    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0> && is_vector_v<vec_type1>, bool> = true>
    [[nodiscard]] constexpr auto operator/(const vec_type0& a, const vec_type1& b) noexcept;

    //div vec/scal
    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    [[nodiscard]] constexpr auto div(const vec_type& a, typename vec_type::scalar b) noexcept;

    //operator /  vec/scal
    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    [[nodiscard]] constexpr auto operator/(const vec_type& a, typename vec_type::scalar b) noexcept;


    //div_assign vec/vec
    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool> = true>
    constexpr vec_type0& div_assign(vec_type0& a, const vec_type1& b) noexcept;

    //operator /=  vec/vec
    template<typename vec_type0, typename vec_type1, std::enable_if_t<is_vector_v<vec_type0>&& is_vector_v<vec_type1>, bool> = true>
    constexpr vec_type0& operator/=(vec_type0& a, const vec_type1& b) noexcept;

    //div_assign vec/scal
    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    constexpr vec_type& div_assign(vec_type& a, typename vec_type::scalar b) noexcept;

    //operator /=  vec/scal
    template<typename vec_type, std::enable_if_t<is_vector_v<vec_type>, bool> = true>
    constexpr vec_type& operator/=(vec_type& a, typename vec_type::scalar b) noexcept;
#pragma endregion

#pragma region Quaternion
    //div quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool> = true>
    [[nodiscard]] constexpr auto div(const quat_type0& a, const quat_type1& b) noexcept;

    //operator /  quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool> = true>
    [[nodiscard]] constexpr auto operator/(const quat_type0& a, const quat_type1& b) noexcept;

    //div quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool> = true>
    [[nodiscard]] constexpr auto div(const quat_type& a, typename quat_type::scalar b) noexcept;

    //operator /  quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool> = true>
    [[nodiscard]] constexpr auto operator/(const quat_type& a, typename quat_type::scalar b) noexcept;


    //div_assign quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool> = true>
    constexpr quat_type0& div_assign(quat_type0& a, const quat_type1& b) noexcept;

    //operator /=  quat/quat
    template<typename quat_type0, typename quat_type1, std::enable_if_t<is_quat_v<quat_type0>&& is_quat_v<quat_type1>, bool> = true>
    constexpr quat_type0& operator/=(quat_type0& a, const quat_type1& b) noexcept;

    //div_assign quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool> = true>
    constexpr quat_type& div_assign(quat_type& a, typename quat_type::scalar b) noexcept;

    //operator /=  quat/scal
    template<typename quat_type, std::enable_if_t<is_quat_v<quat_type>, bool> = true>
    constexpr quat_type& operator/=(quat_type& a, typename quat_type::scalar b) noexcept;
#pragma endregion

}

#include "division.inl"
