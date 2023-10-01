#pragma once
#include <atomic>

#include <rsl/delegate>
#include <rsl/time>

#include "core/engine/engine.hpp"
#include "core/engine/enginesubsystem.hpp"

namespace rythe::core::scheduling
{
    //struct main_clock_time
    //{
    //    using type = rsl::time64;
    //};

    //struct main_clock : public rsl::main_clock, rythe::core::EngineSubSystem<rsl::stopwatch<main_clock_time, std::chrono::high_resolution_clock>>
    //{
    //public:
    //    using time_type = main_clock_time::type;
    //    using span_type = rsl::time_span<time_type>;
    //    using clock_type = std::chrono::high_resolution_clock;

    //private:
    //    const std::chrono::time_point<clock_type> m_start = clock_type::now();

    //public:

    //    span_type start_point() const noexcept
    //    {
    //        return span_type(m_start.time_since_epoch());
    //    }

    //    span_type elapsed_time() const noexcept
    //    {
    //        return span_type(clock_type::now() - m_start);
    //    }

    //    span_type now() const noexcept
    //    {
    //        return span_type(clock_type::now() - m_start);
    //    }
    //};

    //extern const main_clock& mainClock;
}
