#include "vector_base.hpp"
#pragma once

#include "../util/type_util.hpp"

namespace rsl::math
{
    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool>>
    auto length(const vec_type& v) noexcept;

    template<typename vec_type, ::std::enable_if_t<is_vector_v<vec_type>, bool>>
    constexpr auto length2(const vec_type& v) noexcept;

    template<typename Scalar, size_type Size>
    const vector<Scalar, Size> vector<Scalar, Size>::one(static_cast<Scalar>(1));

    template<typename Scalar, size_type Size>
    const vector<Scalar, Size> vector<Scalar, Size>::zero(static_cast<Scalar>(0));

    template<typename Scalar, size_type Size>
    constexpr vector<Scalar, Size>::vector() noexcept { for (size_type i = 0; i < size; i++) data[i] = static_cast<scalar>(0); }

    template<typename Scalar, size_type Size>
    constexpr vector<Scalar, Size>::vector(scalar s) noexcept { for (size_type i = 0; i < size; i++) data[i] = s; }

    template<typename Scalar, size_type Size>
    template<typename Scal, ::std::enable_if_t<!::std::is_same_v<Scalar, Scal>, bool>>
    constexpr vector<Scalar, Size>::vector(const vector<Scal, size>& other) noexcept
    {
        for (size_type i = 0; i < size; i++) data[i] = static_cast<scalar>(other.data[i]);
    }

    template<typename Scalar, size_type Size>
    template<typename vec_type, ::std::enable_if_t<Size != vec_type::size, bool>>
    constexpr vector<Scalar, Size>::vector(const vec_type& other) noexcept
    {
        if constexpr (size > vec_type::size)
        {
            for (size_type i = 0; i < vec_type::size; i++)
                data[i] = static_cast<scalar>(other.data[i]);

            for (size_type i = vec_type::size; i < size; i++)
                data[i] = static_cast<scalar>(0);
        }
        else
        {
            for (size_type i = 0; i < size; i++)
                data[i] = static_cast<scalar>(other.data[i]);
        }
    }

    template<typename Scalar, size_type Size>
    [[nodiscard]] constexpr Scalar& vector<Scalar, Size>::operator[](size_type i) noexcept
    {
        rsl_assert_msg((i >= 0) && (i < size), "vector subscript out of range"); return data[i];
    }

    template<typename Scalar, size_type Size>
    [[nodiscard]] constexpr const Scalar& vector<Scalar, Size>::operator[](size_type i) const noexcept
    {
        rsl_assert_msg((i >= 0) && (i < size), "vector subscript out of range"); return data[i];
    }

    template<typename Scalar, size_type Size>
    [[nodiscard]] r_always_inline Scalar vector<Scalar, Size>::length() const noexcept { return ::rsl::math::length(*this); }

    template<typename Scalar, size_type Size>
    [[nodiscard]] constexpr Scalar vector<Scalar, Size>::length2() const noexcept { return ::rsl::math::length2(*this); }

    template<size_type I, typename Scalar, size_type Size>
    inline r_always_inline Scalar& get(vector<Scalar, Size>& val) { return val[I]; }
}

template<::std::size_t I, typename Scalar, ::std::size_t Size>
struct ::std::tuple_element<I, ::rsl::math::vector<Scalar, Size>> { using type = Scalar; };

namespace std
{
    template<::std::size_t I, typename Scalar, ::std::size_t Size>
    inline r_always_inline Scalar& get(::rsl::math::vector<Scalar, Size>& val) { return ::rsl::math::get<I>(val); }
}

template<typename Scalar, ::std::size_t Size>
struct ::std::tuple_size<::rsl::math::vector<Scalar, Size>>
    : public std::integral_constant<::std::size_t, Size> {};

template<typename Scalar, ::std::size_t Size>
struct ::std::tuple_size<const ::rsl::math::vector<Scalar, Size>>
    : public std::integral_constant<::std::size_t, Size> {};

template<typename Scalar, ::std::size_t Size>
struct ::std::tuple_size<volatile ::rsl::math::vector<Scalar, Size>>
    : public std::integral_constant<::std::size_t, Size> {};

template<typename Scalar, ::std::size_t Size>
struct ::std::tuple_size<const volatile ::rsl::math::vector<Scalar, Size>>
    : public std::integral_constant<::std::size_t, Size> {};
