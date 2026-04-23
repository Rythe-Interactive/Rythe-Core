#pragma once
#include <rsl/utilities>
#include <rsl/reflection>
#include <rsl/string>
#include <rsl/time>

#include "module.hpp"

namespace rythe::core
{
    struct entity
    {};

    template<typename Component>
    concept component_type = rsl::trivial_type<Component> && rsl::standard_layout_type<Component>;

    RYTHE_DECLARE_OPAQUE_HANDLE(process_chain_handle)

    template<typename...>
    struct reads
    {};

    template <typename...>
    struct writes
    {};

    template <typename...>
    struct emits
    {};

    template <typename...>
    struct destroys
    {};

    template<typename...>
    class process_context
    {
    public:
        template<component_type ComponentType>
        [[nodiscard]] const ComponentType& read();

        template <component_type ComponentType>
        [[nodiscard]] const ComponentType& read(entity ent);

        template <component_type ComponentType>
        [[nodiscard]] ComponentType& write();

        template <component_type ComponentType>
        [[nodiscard]] ComponentType& write(entity ent);

        template <component_type ComponentType>
        ComponentType& add_component(ComponentType&& = {});

        template <component_type ComponentType>
        ComponentType& add_component(entity ent, ComponentType&& = {});

        template <component_type ComponentType>
        bool remove_component();

        template <component_type ComponentType>
        bool remove_component(entity ent);

        rsl::tm::span32 deltaTime;
        rsl::tm::span32 time;
    };

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

        process_chain_builder& interval(rsl::tm::span32 timeSpan);

        template<typename ProcessFunc>
        process_chain_builder& add_parallel_process(ProcessFunc&& func);

        template<typename ProcessFunc>
        process_chain_builder& add_sequential_process(ProcessFunc&& func);
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
