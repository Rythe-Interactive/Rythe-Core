#pragma once
#include "system.hpp"

namespace rythe::core
{
    inline process_hook_builder& process_hook_builder::after(const process_chain_handle handle)
    {
        m_value.requirements.emplace_back(
                process_hook_requirement{
                    .chain = handle,
                    .type = process_hook_requirement_type::after
                }
            );
        return *this;
    }

    inline process_hook_builder& process_hook_builder::after(const rsl::string_view processChainName)
    {
        m_value.requirements.emplace_back(
                process_hook_requirement{
                    .chain = m_processGraph->get_process_chain(processChainName),
                    .type = process_hook_requirement_type::after
                }
            );
        return *this;
    }

    inline process_hook_builder& process_hook_builder::before(const process_chain_handle handle)
    {
        m_value.requirements.emplace_back(
                process_hook_requirement{
                    .chain = handle,
                    .type = process_hook_requirement_type::before
                }
            );
        return *this;
    }

    inline process_hook_builder& process_hook_builder::before(const rsl::string_view processChainName)
    {
        m_value.requirements.emplace_back(
                process_hook_requirement {
                    .chain = m_processGraph->get_process_chain(processChainName),
                    .type = process_hook_requirement_type::before
                }
            );
        return *this;
    }

    template <component_type ComponentType>
    process_hook_builder& process_hook_builder::on_create()
    {
        m_value.requirements.emplace_back(
                process_hook_requirement {
                    .componentType = rsl::type_id<ComponentType>(),
                    .type = process_hook_requirement_type::construct
                }
            );
        return *this;
    }

    template <component_type ComponentType>
    process_hook_builder& process_hook_builder::on_destroy()
    {
        m_value.requirements.emplace_back(
                process_hook_requirement {
                    .componentType = rsl::type_id<ComponentType>(),
                    .type = process_hook_requirement_type::destroy
                }
            );
        return *this;
    }

    inline process_hook_builder& process_hook_builder::interval(const rsl::time_span timeSpan) noexcept
    {
        m_value.interval = timeSpan;
        return *this;
    }

    inline process_hook_builder::process_hook_builder(const rsl::size_type index, const rsl::pointer<process_graph_builder> processGraph, const rsl::pointer<process_chain_builder> processChainBuilder) noexcept
        : m_index(index), m_processChainBuilder(processChainBuilder), m_processGraph(processGraph)
    {
    }

    inline bool process_hook_builder::is_valid() const noexcept
    {
        return m_index != rsl::npos;
    }

    inline process_chain_builder& process_chain_builder::add_hook()
    {
        m_currentHookBuilder = process_hook_builder(m_value.hooks.size(), m_processGraph, { this });
        m_value.hooks.emplace_back();
        return *this;
    }

    inline process_chain_builder& process_chain_builder::after(const process_chain_handle handle)
    {
        validate_hook_builder();
        m_currentHookBuilder.after(handle);
        return *this;
    }

    inline process_chain_builder& process_chain_builder::after(const rsl::string_view processChainName)
    {
        validate_hook_builder();
        m_currentHookBuilder.after(processChainName);
        return *this;
    }

    inline process_chain_builder& process_chain_builder::before(const process_chain_handle handle)
    {
        validate_hook_builder();
        m_currentHookBuilder.before(handle);
        return *this;
    }

    inline process_chain_builder& process_chain_builder::before(const rsl::string_view processChainName)
    {
        validate_hook_builder();
        m_currentHookBuilder.before(processChainName);
        return *this;
    }

    template <component_type ComponentType>
    process_chain_builder& process_chain_builder::on_create()
    {
        validate_hook_builder();
        m_currentHookBuilder.on_create<ComponentType>();
        return *this;
    }

    template <component_type ComponentType>
    process_chain_builder& process_chain_builder::on_destroy()
    {
        validate_hook_builder();
        m_currentHookBuilder.on_destroy<ComponentType>();
        return *this;
    }

    inline process_chain_builder& process_chain_builder::interval(const rsl::time_span timeSpan) noexcept
    {
        validate_hook_builder();
        m_currentHookBuilder.interval(timeSpan);
        return *this;
    }

    template <typename ProcessImplType>
    process_chain_builder& process_chain_builder::add_parallel_process(ProcessImplType&& func)
    {
        m_value.processes.emplace_back(process_type::parallel, rsl::forward<ProcessImplType>(func));
        return *this;
    }

    template <typename ProcessImplType>
    process_chain_builder& process_chain_builder::add_sequential_process(ProcessImplType&& func)
    {
        m_value.processes.emplace_back(process_type::sequential, rsl::forward<ProcessImplType>(func));
        return *this;
    }

    inline void process_chain_builder::validate_hook_builder()
    {
        if (!m_currentHookBuilder.is_valid())
        {
            add_hook();
        }
    }

    inline process_chain_builder::process_chain_builder(const rsl::string_view name, const rsl::pointer<process_graph_builder> processGraph) noexcept : m_currentHookBuilder(), m_value(rsl::dynamic_string::from_view(name)), m_processGraph(processGraph)
    {
    }
}
