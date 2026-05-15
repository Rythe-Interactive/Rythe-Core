#pragma once
#include <rsl/containers>
#include <rsl/reflection>
#include <rsl/time>

#include "component.hpp"
#include "module.hpp"
#include "process_context.hpp"

namespace rythe::core
{
    RYTHE_DECLARE_OPAQUE_HANDLE(process_chain_handle)

    enum struct [[rythe_closed_enum]] process_hook_requirement_type
    {
        before,
        after,
        destroy,
        construct,
    };

    struct process_hook_requirement
    {
        union
        {
            process_chain_handle chain;
            rsl::id_type componentType;
        };

        process_hook_requirement_type type;
    };

    struct process_hook
    {
        rsl::dynamic_array<process_hook_requirement> requirements;
        rsl::time_span interval = rsl::time_span::zero;
    };

    class process_hook_builder
    {
    public:
        process_hook_builder(process_hook_builder&&) noexcept;
        process_hook_builder& operator=(process_hook_builder&& src) noexcept;
        ~process_hook_builder();

        [[rythe_always_inline]] process_hook_builder& after(process_chain_handle handle);
        [[rythe_always_inline]] process_hook_builder& after(rsl::string_view processChainName);
        [[rythe_always_inline]] process_hook_builder& before(process_chain_handle handle);
        [[rythe_always_inline]] process_hook_builder& before(rsl::string_view processChainName);

        template <component_type ComponentType>
        [[rythe_always_inline]] process_hook_builder& on_create();
        template <component_type ComponentType>
        [[rythe_always_inline]] process_hook_builder& on_destroy();

        [[rythe_always_inline]] process_hook_builder& interval(rsl::time_span timeSpan) noexcept;

    private:
        friend class process_graph_builder;
        friend class process_chain_builder;

        [[rythe_always_inline]] process_hook_builder() noexcept = default;
        [[rythe_always_inline]] process_hook_builder(rsl::size_type index, rsl::pointer<process_graph_builder> processGraph, rsl::pointer<process_chain_builder> processChainBuilder) noexcept;

        [[rythe_always_inline]] bool is_valid() const noexcept;

        process_hook m_value;
        rsl::size_type m_index = rsl::npos;
        rsl::pointer<process_chain_builder> m_processChainBuilder;
        rsl::pointer<process_graph_builder> m_processGraph;
    };

    struct process_chain
    {
        rsl::dynamic_string name;
        rsl::dynamic_array<process_hook> hooks;
        rsl::dynamic_array<process_function> processes;
    };

    class process_chain_builder
    {
    public:
        process_chain_builder(process_chain_builder&&) noexcept = default;
        ~process_chain_builder();

        [[rythe_always_inline]] process_chain_builder& add_hook();

        [[rythe_always_inline]] process_chain_builder& after(process_chain_handle handle);
        [[rythe_always_inline]] process_chain_builder& after(rsl::string_view processChainName);
        [[rythe_always_inline]] process_chain_builder& before(process_chain_handle handle);
        [[rythe_always_inline]] process_chain_builder& before(rsl::string_view processChainName);

        template <component_type ComponentType>
        [[rythe_always_inline]] process_chain_builder& on_create();
        template <component_type ComponentType>
        [[rythe_always_inline]] process_chain_builder& on_destroy();

        [[rythe_always_inline]] process_chain_builder& interval(rsl::time_span timeSpan) noexcept;

        template <typename ProcessImplType>
        [[rythe_always_inline]] process_chain_builder& add_parallel_process(ProcessImplType&& func);

        template <typename ProcessImplType>
        [[rythe_always_inline]] process_chain_builder& add_sequential_process(ProcessImplType&& func);

    private:
        friend class process_graph_builder;
        friend class process_hook_builder;

        [[rythe_always_inline]] void validate_hook_builder();

        void submit(process_hook_builder&& hook) noexcept;

        [[rythe_always_inline]] process_chain_builder(rsl::string_view name, rsl::pointer<process_graph_builder> processGraph) noexcept;

        process_hook_builder m_currentHookBuilder;
        process_chain m_value;
        rsl::pointer<process_graph_builder> m_processGraph;
    };

    class process_graph_builder
    {
    public:
        [[nodiscard]] process_chain_builder create_process_chain(rsl::string_view processChainName);
        [[nodiscard]] process_chain_handle get_process_chain(rsl::string_view processChainName);
        [[nodiscard]] bool process_chain_exists(rsl::string_view processChainName) const noexcept;
        [[nodiscard]] bool process_chain_exists(process_chain_handle handle) const noexcept;

        void print();
    private:
        friend class process_chain_builder;

        process_chain_handle create_process_chain_impl(rsl::string_view processChainName);
        void submit(process_chain_builder&& processChain) noexcept;

        rsl::dynamic_map<rsl::dynamic_string, process_chain_handle> m_chainMap;
        rsl::dynamic_array<process_chain> m_chains;
    };

    struct [[rsl_reflect(rsl::custom_attribute, rsl::restrict_function_signature(rsl::result<void>(rythe::core::process_graph_builder&)))]] system_function {};

} // namespace rythe::core

#include "system.inl"
