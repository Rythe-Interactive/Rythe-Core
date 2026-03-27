#pragma once

namespace rythe::core
{
    inline rsl::type_map& this_program::get_context() noexcept
    {
        return get_instance().get_context();
    }

    inline bool this_program::is_running() noexcept
    {
        return get_instance().is_running();
    }

    inline void this_program::stop() noexcept
    {
        get_instance().stop();
    }

    inline rsl::type_map& program::get_context() noexcept
    {
        return m_context;
    }

    inline const rsl::type_map& program::get_context() const noexcept
    {
        return m_context;
    }

    inline bool program::is_running() const
    {
        return m_running;
    }

    inline void program::stop()
    {
        m_running = false;
    }
} // namespace rythe::core
