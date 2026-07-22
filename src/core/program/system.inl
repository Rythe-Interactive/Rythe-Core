#pragma once
#include "system.hpp"

namespace rythe::core
{
    template <component_type ComponentType>
    process_hook_builder& process_hook_builder::on_create()
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(
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
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(
                process_hook_requirement {
                    .componentType = rsl::type_id<ComponentType>(),
                    .type = process_hook_requirement_type::destroy
                }
            );
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

    template <process_function_type ProcessImplType>
    process_chain_builder& process_chain_builder::add_parallel_process(ProcessImplType&& func)
    {
        m_processGraph->get_process_chain(m_handle)->processes.emplace_back(
                process_type::parallel, rsl::forward<ProcessImplType>(func));
        return *this;
    }

    template <process_function_type ProcessImplType>
    process_chain_builder& process_chain_builder::add_sequential_process(ProcessImplType&& func)
    {
        m_processGraph->get_process_chain(m_handle)->processes.emplace_back(
                process_type::sequential, rsl::forward<ProcessImplType>(func));
        return *this;
    }
}
