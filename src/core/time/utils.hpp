#pragma once
#include <core/time/time_span.hpp>

namespace rythe::core::time
{
    template<typename precision = fast_time>
    constexpr time_span<precision> hours(precision amount) noexcept;

    template<typename precision = fast_time>
    constexpr time_span<precision> minutes(precision amount) noexcept;

    template<typename precision = fast_time>
    constexpr time_span<precision> seconds(precision amount) noexcept;

    template<typename precision = fast_time>
    constexpr time_span<precision> milliseconds(precision amount) noexcept;

    template<typename precision = fast_time>
    constexpr time_span<precision> microseconds(precision amount) noexcept;

    template<typename precision = fast_time>
    constexpr time_span<precision> nanoseconds(precision amount) noexcept;

    namespace literals
    {
        constexpr span operator "" _hr(float_max amount) noexcept;
        constexpr span operator "" _hr(rsl::uint_max amount) noexcept;

        constexpr span operator "" _min(float_max amount) noexcept;
        constexpr span operator "" _min(rsl::uint_max amount) noexcept;

        constexpr span operator "" _s(float_max amount) noexcept;
        constexpr span operator "" _s(rsl::uint_max amount) noexcept;

        constexpr span operator "" _ms(float_max amount) noexcept;
        constexpr span operator "" _ms(rsl::uint_max amount) noexcept;

        constexpr span operator "" _us(float_max amount) noexcept;
        constexpr span operator "" _us(rsl::uint_max amount) noexcept;

        constexpr span operator "" _ns(float_max amount) noexcept;
        constexpr span operator "" _ns(rsl::uint_max amount) noexcept;
    }
}

#include <core/time/utils.inl>
