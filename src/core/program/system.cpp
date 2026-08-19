#include "system.hpp"

#include <rsl/logging>

namespace rythe::core
{
    process_hook_builder::process_hook_builder(process_hook_builder&& src) noexcept
        : m_index(src.m_index), m_processChainBuilder(rsl::move(src.m_processChainBuilder)), m_processGraph(src.m_processGraph)
    {
        src.m_index = rsl::npos;
    }

    process_hook_builder& process_hook_builder::operator=(process_hook_builder&& src) noexcept
    {
        this->~process_hook_builder();
        new(this) process_hook_builder(rsl::move(src));
        return *this;
    }

    process_hook_builder& process_hook_builder::after(const process_chain_handle handle)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(
                process_hook_requirement{ .chain = handle, .type = process_hook_requirement_type::after });
        return *this;
    }

    process_hook_builder& process_hook_builder::after(const rsl::string_view processChainName)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(process_hook_requirement{
                .chain = m_processGraph->get_process_chain(processChainName),
                                                                     .type = process_hook_requirement_type::after });
        return *this;
    }

    process_hook_builder& process_hook_builder::before(const process_chain_handle handle)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(
                process_hook_requirement{ .chain = handle, .type = process_hook_requirement_type::before });
        return *this;
    }

    process_hook_builder& process_hook_builder::before(const rsl::string_view processChainName)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(process_hook_requirement{
                .chain = m_processGraph->get_process_chain(processChainName),
                                                                     .type = process_hook_requirement_type::before });
        return *this;
    }

    process_hook_builder& process_hook_builder::dont_overlap(const process_chain_handle handle)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(
                process_hook_requirement{ .chain = handle, .type = process_hook_requirement_type::no_overlap });
        return *this;
    }

    process_hook_builder& process_hook_builder::dont_overlap(const rsl::string_view processChainName)
    {
        m_processChainBuilder->get_process_hook(m_index)->requirements.emplace_back(process_hook_requirement{
                .chain = m_processGraph->get_process_chain(processChainName),
                                                                     .type = process_hook_requirement_type::no_overlap });
        return *this;
    }

    process_hook_builder& process_hook_builder::interval(const rsl::time_span timeSpan) noexcept
    {
        m_processChainBuilder->get_process_hook(m_index)->interval = timeSpan;
        return *this;
    }

    process_hook_builder::process_hook_builder(
            const rsl::size_type index,
            const rsl::pointer<process_graph_builder> processGraph,
            const rsl::pointer<process_chain_builder> processChainBuilder) noexcept
        : m_index(index),
          m_processChainBuilder(processChainBuilder),
          m_processGraph(processGraph)
    {}

    bool process_hook_builder::is_valid() const noexcept
    {
        return m_index != rsl::npos;
    }

    process_chain_builder& process_chain_builder::add_hook()
    {
        rsl::pointer<process_chain> processChain = m_processGraph->get_process_chain(m_handle);
        m_currentHookBuilder = process_hook_builder(processChain->hooks.size(), m_processGraph, { this });
        processChain->hooks.emplace_back();
        return *this;
    }

    process_chain_builder& process_chain_builder::after(const process_chain_handle handle)
    {
        validate_hook_builder();
        m_currentHookBuilder.after(handle);
        return *this;
    }

    process_chain_builder& process_chain_builder::after(const rsl::string_view processChainName)
    {
        validate_hook_builder();
        m_currentHookBuilder.after(processChainName);
        return *this;
    }

    process_chain_builder& process_chain_builder::before(const process_chain_handle handle)
    {
        validate_hook_builder();
        m_currentHookBuilder.before(handle);
        return *this;
    }

    process_chain_builder& process_chain_builder::before(const rsl::string_view processChainName)
    {
        validate_hook_builder();
        m_currentHookBuilder.before(processChainName);
        return *this;
    }

    process_chain_builder& process_chain_builder::dont_overlap(const process_chain_handle handle)
    {
        validate_hook_builder();
        m_currentHookBuilder.dont_overlap(handle);
        return *this;
    }

    process_chain_builder& process_chain_builder::dont_overlap(const rsl::string_view processChainName)
    {
        validate_hook_builder();
        m_currentHookBuilder.dont_overlap(processChainName);
        return *this;
    }

    process_chain_builder& process_chain_builder::interval(const rsl::time_span timeSpan) noexcept
    {
        validate_hook_builder();
        m_currentHookBuilder.interval(timeSpan);
        return *this;
    }

    void process_chain_builder::validate_hook_builder()
    {
        if (!m_currentHookBuilder.is_valid()) { add_hook(); }
    }

    rsl::pointer<process_hook> process_chain_builder::get_process_hook(const size_t index)
    {
        return { &m_processGraph->get_process_chain(m_handle)->hooks[index] };
    }

    process_chain_builder::process_chain_builder(
            const process_chain_handle handle,
            const rsl::pointer<process_graph_builder> processGraph) noexcept
        : m_currentHookBuilder(),
          m_handle(handle),
          m_processGraph(processGraph)
    {}

    process_chain_builder process_graph_builder::create_process_chain(const rsl::string_view processChainName)
    {
        process_chain_handle handle = create_process_chain_impl(processChainName);
        rsl_assert_msg_rarely(!process_chain_exists(handle), "Duplicate process chain creation requests.");
        return process_chain_builder(handle, { this });
    }

    process_chain_builder process_graph_builder::create_process_chain(const rsl::source_location anonymousLoc)
    {
        return create_process_chain(rsl::format("{}:{},{}", anonymousLoc.file_name(), anonymousLoc.line(), anonymousLoc.column()));
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
        return !chain.hooks.is_empty() && !chain.processes.is_empty();
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
                        case process_hook_requirement_type::no_overlap:
                            requirementType = "no_overlap";
                            requirementValue = static_cast<rsl::id_type>(requirement.chain);
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

    rsl::pointer<process_chain> process_graph_builder::get_process_chain(process_chain_handle handle)
    {
        const rsl::size_type index = static_cast<rsl::size_type>(handle);
        if (index > m_chains.size())
        {
            return { nullptr };
        }
        return { &m_chains[index] };
    }

    process_chain_handle process_graph_builder::create_process_chain_impl(const rsl::string_view processChainName)
    {
        rsl_assert_invalid_operation(!processChainName.is_empty());
        auto [handle, newItem] = m_chainMap.try_emplace(processChainName);

        if (newItem)
        {
            handle = static_cast<process_chain_handle>(m_chains.size());
            m_chains.emplace_back(process_chain{ .name = rsl::dynamic_string::from_view(processChainName), .hooks{}, .processes{} });
        }

        return handle;
    }
}
