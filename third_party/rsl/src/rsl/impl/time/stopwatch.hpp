#pragma once
#include <chrono>

#include "../defines.hpp"
#include "../util/primitives.hpp"

#include "time_point.hpp"


namespace rsl
{
    template<time_duration_rep precision = fast_time, chrono_clock clock_t = std::chrono::high_resolution_clock>
    struct stopwatch
    {
    public:
        using time_type = precision;
        using span_type = time_span<time_type>;
        using time_point_type = time_point<precision, clock_t>;
        using clock_type = clock_t;

    private:
        std::chrono::time_point<clock_type> m_start{ clock_type::now() };

    public:
        r_always_inline void      start()   noexcept       { m_start = clock_type::now(); }
        r_always_inline span_type end()     const noexcept { return span_type(clock_type::now() - m_start); }

        r_always_inline span_type restart() noexcept
        {
            auto startTime = clock_type::now();
            span_type time(startTime - m_start);
            m_start = startTime;
            return time;
        }

        r_always_inline time_point_type start_point()  const noexcept { return time_point_type{ m_start.time_since_epoch() }; }
        r_always_inline time_point_type current_point()  const noexcept { return time_point_type{ clock_type::now() }; }
        r_always_inline span_type elapsed_time() const noexcept { return span_type{ clock_type::now() - m_start }; }

        r_always_inline void fast_forward(span_type time) noexcept(std::is_arithmetic_v<time_type>) { m_start -= std::chrono::duration_cast<typename clock_type::duration>(time.duration); }
        r_always_inline void rewind(span_type time)       noexcept(std::is_arithmetic_v<time_type>) { m_start += std::chrono::duration_cast<typename clock_type::duration>(time.duration); }
    };

    using timer = stopwatch<>;
}
