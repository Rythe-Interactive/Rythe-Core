#include <core/scheduling/process.hpp>

namespace rythe::core::scheduling
{
    Process::Process(const std::string& name, rsl::id_type nameHash, rsl::span interval) : m_name(name), m_nameHash(nameHash)
    {
        setInterval(interval);
    }

    rsl::id_type Process::id() const noexcept
    {
        return m_nameHash;
    }

    bool Process::inUse() const noexcept
    {
        return m_hooks.size();
    }

    void Process::setOperation(rsl::delegate<void(rsl::time_span<rsl::fast_time>)>&& operation) noexcept
    {
        m_operation = operation;
    }

    void Process::setInterval(rsl::span interval) noexcept
    {
        m_fixedTimeStep = interval != rsl::span::zero();
        m_interval = interval;
    }

    std::unordered_set<rsl::id_type>& Process::hooks() noexcept
    {
        return m_hooks;
    }

    void Process::execute(rsl::span deltaTime)
    {
        if (!m_fixedTimeStep)
        {
            m_operation(deltaTime);
        }
        else
        {
            m_timebuffer += deltaTime;
            if (m_timebuffer >= m_interval)
            {
                m_operation(m_timebuffer);
                m_timebuffer -= m_interval;
            }
        }
    }
}
