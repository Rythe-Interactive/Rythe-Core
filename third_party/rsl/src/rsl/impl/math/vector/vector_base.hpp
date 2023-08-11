#pragma once
#include <tuple>

#include "../../defines.hpp"
#include "../../util/assert.hpp"
#include "../../util/primitives.hpp"

namespace rsl::math
{
    struct vector_base {};

    template<typename Scalar, size_type Size>
    struct vector : vector_base
    {
        using scalar = Scalar;
        static constexpr size_type size = Size;
        using type = vector<Scalar, Size>;

        scalar data[size];

        static const vector one;
        static const vector zero;

        constexpr vector() noexcept;
        constexpr vector(const vector&) noexcept = default;
        explicit constexpr vector(scalar s) noexcept;

        template<typename Scal, ::std::enable_if_t<!::std::is_same_v<scalar, Scal>, bool> = true>
        constexpr explicit vector(const vector<Scal, size>& other) noexcept;

        template<typename vec_type, ::std::enable_if_t<Size != vec_type::size, bool> = true>
        constexpr vector(const vec_type& other) noexcept;

        constexpr vector& operator=(const vector&) noexcept = default;

        [[nodiscard]] constexpr scalar& operator[](size_type i) noexcept;
        [[nodiscard]] constexpr const scalar& operator[](size_type i) const noexcept;

        [[nodiscard]] r_always_inline scalar length() const noexcept;
        [[nodiscard]] constexpr scalar length2() const noexcept;
    };
}
