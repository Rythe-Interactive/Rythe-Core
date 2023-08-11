#pragma once
#include <chrono>

#include "../util/primitives.hpp"
#include "../util/concepts.hpp"

#include "time_span.hpp"

namespace rsl {
    template<typename Clock>
    concept chrono_clock = requires {
        { Clock::now() } -> specialization_of<std::chrono::time_point>;
            requires specialization_of<typename Clock::duration, std::chrono::duration>;
    };

    template<time_duration_rep precision = fast_time, chrono_clock clock_t = std::chrono::high_resolution_clock>
    struct time_point { // represents a point in time
    private:
        using rep = typename clock_t::rep;
        using tp_t = typename clock_t::time_point;

        template<time_duration_rep T>
        [[nodiscard]] constexpr days_duration<T> d_dur()              const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<days_duration<T>>(std::chrono::abs(duration)); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr hours_duration<T> h_dur()             const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<hours_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>()); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr minutes_duration<T> m_dur()           const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<minutes_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>() - h_dur<time_large>()); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr seconds_duration<T> s_dur()           const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<seconds_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>() - h_dur<time_large>() - m_dur<time_large>()); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr milli_seconds_duration<T> milli_dur() const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<milli_seconds_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>() - h_dur<time_large>() - m_dur<time_large>() - s_dur<time_large>()); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr micro_seconds_duration<T> micro_dur() const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<micro_seconds_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>() - h_dur<time_large>() - m_dur<time_large>() - s_dur<time_large>() - milli_dur<time_large>()); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr nano_seconds_duration<T> nano_dur()   const noexcept(std::is_arithmetic_v<rep>)           { return std::chrono::duration_cast<nano_seconds_duration<T>>(std::chrono::abs(duration) - d_dur<time_large>() - h_dur<time_large>() - m_dur<time_large>() - s_dur<time_large>() - milli_dur<time_large>() - micro_dur<time_large>()); }

    public:
        using time_type = precision;
        using span_type = time_span<time_type>;
        using duration_type = typename clock_t::duration;
        using clock_type = clock_t;

        duration_type duration{ duration_type::zero() }; // duration since the epoch

        constexpr time_point() = default;

        constexpr explicit time_point(const duration_type& other) noexcept(std::is_arithmetic_v<rep>) /* strengthened */        : duration(other) {}
        constexpr explicit time_point(const tp_t& other) noexcept(std::is_arithmetic_v<rep>) /* strengthened */                 : duration(other.time_since_epoch()) {}

        template <std::convertible_to<duration_type> other_duration>
        constexpr time_point(const time_point<clock_t, other_duration>& other)
        noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<typename other_duration::rep>) /* strengthened */            : duration(other.duration) {}

        [[nodiscard]] constexpr span_type time_since_epoch() const noexcept(std::is_arithmetic_v<rep>) /* strengthened */       { return span_type{ duration }; }

        constexpr time_point& operator++()   noexcept(std::is_arithmetic_v<rep>) /* strengthened */                             { ++duration; return *this; }
        constexpr time_point operator++(int) noexcept(std::is_arithmetic_v<rep>) /* strengthened */                             { return time_point{ duration++ }; }
        constexpr time_point& operator--()   noexcept(std::is_arithmetic_v<rep>) /* strengthened */                             { --duration; return *this; }
        constexpr time_point operator--(int) noexcept(std::is_arithmetic_v<rep>) /* strengthened */                             { return time_point{ duration-- }; }

        constexpr time_point& operator+=(const duration_type& _Dur) noexcept(std::is_arithmetic_v<rep>) /* strengthened */      { duration += _Dur; return *this; }
        constexpr time_point& operator-=(const duration_type& _Dur) noexcept(std::is_arithmetic_v<rep>) /* strengthened */      { duration -= _Dur; return *this; }

        [[nodiscard]] constexpr operator tp_t() const noexcept { return tp_t{ duration }; }

        [[nodiscard]] static constexpr time_point min() noexcept                                                                { return time_point{ duration_type::min() }; }
        [[nodiscard]] static constexpr time_point max() noexcept                                                                { return time_point{ duration_type::max() }; }

        template<time_duration_rep T>
        [[nodiscard]] constexpr T hours()        const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return h_dur<T>().count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T minutes()      const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return m_dur<T>().count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T seconds()      const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return s_dur<T>().count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T milliseconds() const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return milli_dur<T>().count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T microseconds() const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return micro_dur<T>().count(); }
        template<time_duration_rep T>
        [[nodiscard]] constexpr T nanoseconds()  const noexcept(std::is_arithmetic_v<rep> && std::is_arithmetic_v<T>)     { return nano_dur<T>().count(); }

        [[nodiscard]] constexpr rsl::hours         hours()        const noexcept(std::is_arithmetic_v<rep>)               { return h_dur<rsl::hours>().count(); }
        [[nodiscard]] constexpr rsl::minutes       minutes()      const noexcept(std::is_arithmetic_v<rep>)               { return m_dur<rsl::minutes>().count(); }
        [[nodiscard]] constexpr rsl::seconds       seconds()      const noexcept(std::is_arithmetic_v<rep>)               { return s_dur<rsl::seconds>().count(); }
        [[nodiscard]] constexpr rsl::milli_seconds milliseconds() const noexcept(std::is_arithmetic_v<rep>)               { return milli_dur<rsl::milli_seconds>().count(); }
        [[nodiscard]] constexpr rsl::micro_seconds microseconds() const noexcept(std::is_arithmetic_v<rep>)               { return micro_dur<rsl::micro_seconds>().count(); }
        [[nodiscard]] constexpr rsl::nano_seconds  nanoseconds()  const noexcept(std::is_arithmetic_v<rep>)               { return nano_dur<rsl::nano_seconds>().count(); }
    };
}

template <rsl::time_duration_rep precision, rsl::chrono_clock clock_t, rsl::time_duration_rep precision2>
[[nodiscard]] constexpr auto operator<=>(const rsl::time_point<precision, clock_t>& lhs, const rsl::time_point<precision2, clock_t>& rhs)
noexcept(std::is_arithmetic_v<typename clock_t::rep>) /* strengthened */
{
    return lhs.duration <=> rhs.duration;
}

template <rsl::time_duration_rep precision, rsl::chrono_clock clock_t, rsl::time_duration_rep precision2>
[[nodiscard]] constexpr rsl::common_time_span<precision, precision2> operator-(const rsl::time_point<precision, clock_t>& lhs, const rsl::time_point<precision2, clock_t>& rhs)
noexcept(std::is_arithmetic_v<typename clock_t::rep>) /* strengthened */ {
    return rsl::common_time_span<precision, precision2> { lhs.duration - rhs.duration };
}
