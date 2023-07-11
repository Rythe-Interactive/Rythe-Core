#pragma once
#include <rsl/time>

#include "core/engine/enginesubsystem.hpp"


namespace rythe::core::time
{

    using main_clock_time = rsl::time64;

    template<>
    struct rsl::stopwatch<main_clock_time, std::chrono::high_resolution_clock> : public EngineSubSystem<rsl::stopwatch<main_clock_time, std::chrono::high_resolution_clock>>
    {
    public:
        using time_type = main_clock_time;
        using span_type = rsl::time_span<time_type>;
        using clock_type = std::chrono::high_resolution_clock;

    private:
        const std::chrono::time_point<clock_type> m_start = clock_type::now();

    public:

        span_type start_point() const noexcept
        {
            return span_type(m_start.time_since_epoch());
        }

        span_type elapsed_time() const noexcept
        {
            return span_type(clock_type::now() - m_start);
        }

        span_type now() const noexcept
        {
            return span_type(clock_type::now() - m_start);
        }
    };

    using main_clock = rsl::stopwatch<main_clock_time, std::chrono::high_resolution_clock>;

    extern const main_clock& mainClock;
}
