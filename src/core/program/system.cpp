#include "system.hpp"

#include <rsl/logging>

namespace rythe::core
{
    process_hook_builder::process_hook_builder(process_hook_builder&& src) noexcept
        : m_value(rsl::move(src.m_value)), m_index(src.m_index), m_processChainBuilder(rsl::move(src.m_processChainBuilder)), m_processGraph(src.m_processGraph)
    {
        src.m_index = rsl::npos;
    }

    process_hook_builder& process_hook_builder::operator=(process_hook_builder&& src) noexcept
    {
        this->~process_hook_builder();
        new(this) process_hook_builder(rsl::move(src));
        return *this;
    }

    process_hook_builder::~process_hook_builder()
    {
        if (is_valid())
        {
            m_processChainBuilder->submit(rsl::move(*this));
        }
    }

    process_chain_builder::~process_chain_builder()
    {
        if (m_currentHookBuilder.is_valid())
        {
            submit(rsl::move(m_currentHookBuilder));
        }
        m_processGraph->submit(rsl::move(*this));
    }

    void process_chain_builder::submit(process_hook_builder&& hook) noexcept
    {
        m_value.hooks[hook.m_index] = rsl::move(hook.m_value);
        hook.m_index = rsl::npos;
    }

    process_chain_builder process_graph_builder::create_process_chain(const rsl::string_view processChainName)
    {
        [[maybe_unused]] process_chain_handle handle = create_process_chain_impl(processChainName);
        rsl_assert_msg_rarely(!process_chain_exists(handle), "Duplicate process chain creation requests.");
        return process_chain_builder(processChainName, { this });
    }

    process_chain_handle process_graph_builder::get_process_chain(const rsl::string_view processChainName)
    {
        return create_process_chain_impl(processChainName);
    }

    bool process_graph_builder::process_chain_exists(const rsl::string_view processChainName) const noexcept
    {
        const process_chain_handle* handle = m_chainMap.find(processChainName);
        if (!handle)
        {
            return false;
        }

        return process_chain_exists(*handle);
    }

    bool process_graph_builder::process_chain_exists(process_chain_handle handle) const noexcept
    {
        const process_chain& chain = m_chains[static_cast<size_t>(handle)];
        return !chain.hooks.empty() && !chain.processes.empty();
    }

    void process_graph_builder::print()
    {
        for (auto& chain : m_chains)
        {
            rsl::log::debug("{}:", chain.name);
            rsl::log::debug("\thooks:");
            for (auto& hook : chain.hooks)
            {
                rsl::log::debug("\t\tinterval: {}", hook.interval);
                rsl::log::debug("\t\trequirements:");
                for (auto& requirement : hook.requirements)
                {
                    rsl::string_view requirementType;
                    rsl::id_type requirementValue;
                    switch (requirement.type)
                    {
                        case process_hook_requirement_type::after:
                            requirementType = "after";
                            requirementValue = static_cast<rsl::id_type>(requirement.chain);
                            break;
                        case process_hook_requirement_type::before:
                            requirementType = "before";
                            requirementValue = static_cast<rsl::id_type>(requirement.chain);
                            break;
                        case process_hook_requirement_type::destroy:
                            requirementType = "destroy";
                            requirementValue = requirement.componentType;
                            break;
                        case process_hook_requirement_type::construct:
                            requirementType = "construct";
                            requirementValue = requirement.componentType;
                            break;
                    }

                    rsl::log::debug("\t\t\t{}: {}", requirementType, requirementValue);
                }
            }

            rsl::log::debug("\tprocesses:");
            for (auto& process : chain.processes)
            {
                rsl::log::debug("\t\ttype: {}", process.type == process_type::sequential ? "sequential" : "parallel");
            }
        }
    }

    process_chain_handle process_graph_builder::create_process_chain_impl(const rsl::string_view processChainName)
    {
        rsl_assert_invalid_operation(!processChainName.empty());
        auto [handle, newItem] = m_chainMap.try_emplace(processChainName);

        if (newItem)
        {
            handle = static_cast<process_chain_handle>(m_chains.size());
            m_chains.emplace_back(process_chain{ .name = rsl::dynamic_string::from_view(processChainName), .hooks{}, .processes{} });
        }

        return handle;
    }

    void process_graph_builder::submit(process_chain_builder&& processChain) noexcept
    {
        process_chain_handle* handle = m_chainMap.find(processChain.m_value.name);
        rsl_assert_invalid_operation(handle != nullptr);
        m_chains[static_cast<size_t>(*handle)] = rsl::move(processChain.m_value);
    }
}
