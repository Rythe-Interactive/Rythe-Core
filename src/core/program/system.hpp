#pragma once
#include <rsl/reflection>
#include <rsl/string>
#include <rsl/time>
#include <rsl/containers>

#include "component.hpp"
#include "module.hpp"
#include "process_context.hpp"

namespace rythe::core
{
    RYTHE_DECLARE_OPAQUE_HANDLE(process_chain_handle)
    RYTHE_DECLARE_OPAQUE_HANDLE(process_hook_handle)

    enum struct [[rythe_closed_enum]] process_hook_type
    {
        before,
        after,
        destroy,
        construct,
    };

    struct process_hook_description
    {
        union
        {
            process_chain_handle chain;
            rsl::id_type componentType;
        };

        process_hook_type type;
    };

    class process_chain_builder
    {
    public:
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
        friend class process_graph;

        process_hook_handle m_hook;
        rsl::time_span m_interval = rsl::time_span::zero;
        rsl::dynamic_array<process_function> m_processes;
        rsl::pointer<process_graph> m_processGraph;
    };

    class process_graph
    {
    public:
        [[nodiscard]] process_chain_builder create_process_chain(rsl::string_view processChainName);
        [[nodiscard]] process_chain_handle find_process_chain(rsl::string_view processChainName);

    private:
        [[nodiscard]] process_hook_handle find_process_hook(const process_hook_description& description);
        friend class process_chain_builder; 
    };

    struct [[rsl_reflect(rsl::custom_attribute, rsl::restrict_function_signature(rsl::result<void>(rythe::core::process_graph&)))]] system_function {};

} // namespace rythe::core

#include "system.inl"
