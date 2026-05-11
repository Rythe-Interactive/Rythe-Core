#pragma once
#include "system.hpp"

namespace rythe::core
{
    inline process_chain_builder& process_chain_builder::after(process_chain_handle handle)
    {
        m_hook = m_processGraph->find_process_hook({ .chain = handle, .type = process_hook_type::after });
        return *this;
    }

    inline process_chain_builder& process_chain_builder::after(rsl::string_view processChainName)
    {
        m_hook = m_processGraph->find_process_hook(
            {
                .chain = m_processGraph->find_process_chain(processChainName),
                .type = process_hook_type::after
            }
        );
        return *this;
    }

    inline process_chain_builder& process_chain_builder::before(process_chain_handle handle)
    {
        m_hook = m_processGraph->find_process_hook({ .chain = handle, .type = process_hook_type::before });
        return *this;
    }

    inline process_chain_builder& process_chain_builder::before(rsl::string_view processChainName)
    {
        m_hook = m_processGraph->find_process_hook(
            {
                .chain = m_processGraph->find_process_chain(processChainName),
                .type = process_hook_type::before
            }
        );
        return *this;
    }

    template <component_type ComponentType>
    process_chain_builder& process_chain_builder::on_create()
    {
        m_hook = m_processGraph->find_process_hook({ .componentType = rsl::type_id<ComponentType>(), .type = process_hook_type::construct });
        return *this;
    }

    template <component_type ComponentType>
    process_chain_builder& process_chain_builder::on_destroy()
    {
        m_hook = m_processGraph->find_process_hook({ .componentType = rsl::type_id<ComponentType>(), .type = process_hook_type::destroy });
        return *this;
    }

    inline process_chain_builder& process_chain_builder::interval(rsl::time_span timeSpan) noexcept
    {
        m_interval = timeSpan;
        return *this;
    }

    template <typename ProcessImplType>
    process_chain_builder& process_chain_builder::add_parallel_process(ProcessImplType&& func)
    {
        m_processes.emplace_back(process_type::parallel, rsl::forward<ProcessImplType>(func));
        return *this;
    }

    template <typename ProcessImplType>
    process_chain_builder& process_chain_builder::add_sequential_process(ProcessImplType&& func)
    {
        m_processes.emplace_back(process_type::sequential, rsl::forward<ProcessImplType>(func));
        return *this;
    }
}
