#include <core/scheduling/clock.hpp>

#include <thread>

namespace rythe::core::scheduling
{
    void Clock::advance(span_type start, span_type elapsed)
    {
        instance.m_lastTickDuration = elapsed;
        instance.m_lastTickStart = start;
        instance.m_onTick(elapsed);
    }

    void Clock::onInit()
    {
        reportDependency<rsl::main_clock>();
        create();
    }

    Clock::time_type Clock::timeScale() noexcept
    {
        return instance.m_timeScale;
    }

    void Clock::setTimeScale(time_type value) noexcept
    {
        instance.m_timeScale = value;
    }

    Clock::span_type Clock::elapsedSinceTickStart() noexcept
    {
        return (rsl::main_clock.current_point() - instance.m_lastTickStart) * instance.m_timeScale;
    }

    Clock::span_type Clock::lastTickDuration() noexcept
    {
        return instance.m_lastTickDuration * instance.m_timeScale;
    }

    Clock::span_type Clock::unscaledElapsedSinceTickStart() noexcept
    {
        return rsl::main_clock.current_point() - instance.m_lastTickStart;
    }

    Clock::span_type Clock::unscaledLastTickDuration() noexcept
    {
        return instance.m_lastTickDuration;
    }

    void Clock::subscribeToTick(const tick_callback_delegate& func)
    {
        instance.m_onTick.push_back(func);
    }

    void Clock::unsubscribeFromTick(const tick_callback_delegate& func)
    {
        instance.m_onTick.remove(func);
    }

    void Clock::setAdvancementProtocol(advancement_protocol protocol) noexcept
    {
        instance.m_protocol = protocol;
    }

    void Clock::setTickSpeed(span_type interval) noexcept
    {
        instance.m_interval = interval;
    }

    void Clock::update()
    {
        auto loopStart = rsl::main_clock.current_point();
        auto elapsedSinceLastTick = loopStart - instance.m_lastTickStart;

        if (instance.m_waitBuffer.nanoseconds() > static_cast<span_type::time_type>(0))
        {
            instance.m_waitBuffer -= elapsedSinceLastTick;
            instance.m_lastTickStart = loopStart;
            return;
        }

        switch (instance.m_protocol)
        {
        case advancement_protocol::Free:
            advance(loopStart, elapsedSinceLastTick);
            break;
        case advancement_protocol::Interval:
            if (elapsedSinceLastTick >= instance.m_interval)
                advance(loopStart, elapsedSinceLastTick);
            break;
        case advancement_protocol::Manual:
            if (instance.m_doTick.exchange(false, std::memory_order_acquire))
                advance(loopStart, elapsedSinceLastTick);
            else
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            break;
        }
    }

    void Clock::pause(span_type duration) noexcept
    {
        instance.m_waitBuffer = duration;
    }

    void Clock::bufferPause(span_type duration) noexcept
    {
        instance.m_waitBuffer += duration;
    }

    void Clock::tick()
    {
        instance.m_doTick.store(true, std::memory_order_release);
    }
}
