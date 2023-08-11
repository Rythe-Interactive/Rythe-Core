#pragma once
#include <chrono>

#include "../util/primitives.hpp"
#include "../util/concepts.hpp"

namespace rsl
{
    template<typename Rep>
    concept time_duration_rep = !is_specialization_v<Rep, std::chrono::duration>;

    template<time_duration_rep precision = nano_seconds>
    using nano_seconds_duration = std::chrono::duration<precision, std::nano>;

    template<time_duration_rep precision = micro_seconds>
    using micro_seconds_duration = std::chrono::duration<precision, std::micro>;

    template<time_duration_rep precision = milli_seconds>
    using milli_seconds_duration = std::chrono::duration<precision, std::milli>;

    template<time_duration_rep precision = seconds>
    using seconds_duration = std::chrono::duration<precision, std::ratio<1>>;

    template<time_duration_rep precision = minutes>
    using minutes_duration = std::chrono::duration<precision, std::ratio<60>>;

    template<time_duration_rep precision = hours>
    using hours_duration = std::chrono::duration<precision, std::ratio_multiply<std::ratio<60>, std::chrono::minutes::period>>;

    template<time_duration_rep precision = days>
    using days_duration = std::chrono::duration<precision, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;

    template<time_duration_rep precision = fast_time>
    struct time_span
    {
        using time_type = precision;
        using duration_type = std::chrono::duration<time_type>;

        duration_type duration{ duration_type::zero() };

        constexpr time_span() noexcept = default;

        constexpr time_span(time_type other) noexcept : duration(other) {}

        template<time_duration_rep other_time, ratio_type ratio>
        constexpr explicit time_span(const std::chrono::duration<other_time, ratio>& other) noexcept
            : duration(std::chrono::duration_cast<duration_type>(other)) {}

        template<time_duration_rep other_time>
        requires (!std::same_as<other_time, time_type>)
        constexpr explicit time_span(const time_span<other_time>& other) noexcept : duration(other.duration) {}

        template<time_duration_rep other_time, ratio_type ratio>
        constexpr explicit time_span(std::chrono::duration<other_time, ratio>&& other) noexcept
            : duration(std::chrono::duration_cast<duration_type>(other)) {}

        template<time_duration_rep other_time>
        requires (!std::same_as<other_time, time_type>)
        constexpr explicit time_span(time_span<other_time>&& other) noexcept : duration(std::move(other.duration)) {}

        template<time_duration_rep other_time>
        requires (!std::same_as<other_time, time_type>)
        constexpr explicit time_span(other_time other) noexcept : duration(other) {}

        template<time_duration_rep other_time>
        constexpr time_span<other_time> cast() const noexcept { return { *this }; }

        template<time_duration_rep T>
        [[nodiscard]] constexpr T hours()        const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<hours_duration<T>>(duration).count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T minutes()      const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<minutes_duration<T>>(duration).count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T seconds()      const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<seconds_duration<T>>(duration).count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T milliseconds() const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<milli_seconds_duration<T>>(duration).count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T microseconds() const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<micro_seconds_duration<T>>(duration).count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T nanoseconds()  const noexcept(std::is_arithmetic_v<time_type> && std::is_arithmetic_v<T>) { return std::chrono::duration_cast<nano_seconds_duration<T>>(duration).count(); }

        [[nodiscard]] constexpr time_type hours()        const noexcept(std::is_arithmetic_v<time_type>)    { return std::chrono::duration_cast<hours_duration<time_type>>(duration).count(); }
        [[nodiscard]] constexpr time_type minutes()      const noexcept(std::is_arithmetic_v<time_type>)    { return std::chrono::duration_cast<minutes_duration<time_type>>(duration).count(); }
        [[nodiscard]] constexpr time_type seconds()      const noexcept(std::is_arithmetic_v<time_type>)    { return duration.count(); }
        [[nodiscard]] constexpr time_type milliseconds() const noexcept(std::is_arithmetic_v<time_type>)    { return std::chrono::duration_cast<milli_seconds_duration<time_type>>(duration).count(); }
        [[nodiscard]] constexpr time_type microseconds() const noexcept(std::is_arithmetic_v<time_type>)    { return std::chrono::duration_cast<micro_seconds_duration<time_type>>(duration).count(); }
        [[nodiscard]] constexpr time_type nanoseconds()  const noexcept(std::is_arithmetic_v<time_type>)    { return std::chrono::duration_cast<nano_seconds_duration<time_type>>(duration).count(); }

        [[nodiscard]] constexpr operator duration_type&()       noexcept       { return duration; }
        [[nodiscard]] constexpr operator const duration_type&() const noexcept { return duration; }
        [[nodiscard]] constexpr operator time_type()            const noexcept { return duration.count(); }

        constexpr time_span& operator++()   noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { ++duration; return *this; }
        constexpr time_span operator++(int) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { return time_span(duration++); }
        constexpr time_span& operator--()   noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { --duration; return *this; }
        constexpr time_span operator--(int) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { return time_span(duration--); }

        template<time_duration_rep other_time>
        constexpr time_span& operator+=(const time_span<other_time>& rhs) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { duration += std::chrono::duration_cast<duration_type>(rhs.duration); return *this; }

        template<time_duration_rep other_time>
        constexpr time_span& operator-=(const time_span<other_time>& rhs) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { duration -= std::chrono::duration_cast<duration_type>(rhs.duration); return *this; }

        template<time_duration_rep other_time>
        constexpr time_span& operator*=(const time_span<other_time>& rhs) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { duration *= std::chrono::duration_cast<duration_type>(rhs.duration); return *this; }

        template<time_duration_rep other_time>
        constexpr time_span& operator/=(const time_span<other_time>& rhs) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { duration /= std::chrono::duration_cast<duration_type>(rhs.duration); return *this; }

        template<time_duration_rep other_time>
        constexpr time_span& operator%=(const time_span<other_time>& rhs) noexcept(std::is_arithmetic_v<time_type>) /* strengthened */        { duration %= std::chrono::duration_cast<duration_type>(rhs.duration); return *this; }

        [[nodiscard]] static constexpr time_span zero() noexcept { return time_span(0); }
        [[nodiscard]] static constexpr time_span min()  noexcept { return time_span(std::chrono::duration_values<time_type>::min()); }
        [[nodiscard]] static constexpr time_span max()  noexcept { return time_span(std::chrono::duration_values<time_type>::max()); }
    };

    template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
    using common_time_span = time_span<std::common_type_t<precisionLHS, precisionRHS>>;
    using span = time_span<>;
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator+(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return rsl::common_time_span<precisionLHS, precisionRHS>(lhs.duration + rhs.duration);
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator-(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return rsl::common_time_span<precisionLHS, precisionRHS>(lhs.duration - rhs.duration);
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator*(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return rsl::common_time_span<precisionLHS, precisionRHS>(lhs.duration * rhs.duration);
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator/(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return rsl::common_time_span<precisionLHS, precisionRHS>(lhs.duration / rhs.duration);
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator%(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return rsl::common_time_span<precisionLHS, precisionRHS>(lhs.duration % rhs.duration);
}

template<rsl::time_duration_rep precisionLHS, rsl::time_duration_rep precisionRHS>
[[nodiscard]] constexpr auto operator<=>(const rsl::time_span<precisionLHS>& lhs, const rsl::time_span<precisionRHS>& rhs)
noexcept(std::is_arithmetic_v<precisionLHS>&& std::is_arithmetic_v<precisionRHS>) /* strengthened */
{
    return lhs.duration.count() <=> rhs.duration.count();
}
