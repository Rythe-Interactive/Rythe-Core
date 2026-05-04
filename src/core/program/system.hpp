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

    class process_chain_builder
    {
    public:
        process_chain_builder& after(process_chain_handle handle);
        process_chain_builder& after(rsl::string_view processChainName);
        process_chain_builder& before(process_chain_handle handle);
        process_chain_builder& before(rsl::string_view processChainName);

        template <component_type ComponentType>
        process_chain_builder& on_create();
        template <component_type ComponentType>
        process_chain_builder& on_destroy();

        process_chain_builder& interval(rsl::time_span timeSpan);

        template <typename ProcessImplType>
        process_chain_builder& add_parallel_process(ProcessImplType&& func)
        {
            process_function processFunc(rsl::forward<ProcessImplType>(func));
        }

        template <typename ProcessImplType>
        process_chain_builder& add_sequential_process(ProcessImplType&& func)
        {
            process_function processFunc(rsl::forward<ProcessImplType>(func));
        }
    };

    class system_context
    {
    public:
        process_chain_builder create_process_chain(rsl::string_view processChainName);
        process_chain_handle find_process_chain(rsl::string_view processChainName);
    };

    class system_registrar
    {
    public:
        system_registrar(rsl::result<void> (*system_name)(rythe::core::system_context&), rsl::string_view systemName);
    };

    struct [[rsl_reflect(rsl::custom_attribute, rsl::restrict_function_signature(rsl::result<void>(rythe::core::system_context&)))]] system_function {};

} // namespace rythe::core
