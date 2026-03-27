#pragma once
#include <rsl/utilities>
#include <rsl/string>
#include <rsl/time>

#include "module.hpp"

namespace rythe::core
{
    struct entity
    {};

    template<typename Component>
    concept component_type = true;

    class system_builder;

    struct system_id
    {
        module_id moduleId;
        rsl::hashed_string_view name;
    };

    struct process_chain_id
    {
        system_id systemId;
        rsl::hashed_string_view name;
    };

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
        process_chain_builder& after(process_chain_id id);
        process_chain_builder& before(process_chain_id id);

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

    class system_builder
    {
    public:
        process_chain_builder create_process_chain(process_chain_id id);
    };

    class system_registrar
    {
    public:
        system_registrar(rsl::result<void>(*system_name)(rythe::core::system_builder&), system_id id);
    };
} // namespace rythe::core

#define RYTHE_DECLARE_SYSTEM(module_name, system_name)                                                                                \
    rythe::core::system_id RYTHE_CONCAT(system_name, _id){ .moduleId = RYTHE_CONCAT(module_name, _id),                                \
                                                           .name = rsl::hashed_string_view::from_array(#system_name) };  

#define RYTHE_DEFINE_SYSTEM(system_name)                                                                                              \
    static rsl::result<void> system_name(rythe::core::system_builder& systemBuilder);                                                 \
    RYTHE_ANON_VAR(rythe::core::system_registrar, systemRegistrar)(&system_name, RYTHE_CONCAT(system_name, _id));                     \
    static rsl::result<void> system_name(rythe::core::system_builder& systemBuilder)                              

#define RYTHE_DECLARE_PUBLIC_PROCESS_CHAIN(system_name, process_chain)                                                                \
    rythe::core::process_chain_id RYTHE_CONCAT(RYTHE_CONCAT(system_name, _), RYTHE_CONCAT(process_chain, _id)){                       \
        .systemId = RYTHE_CONCAT(system_name, _id), .name = rsl::hashed_string_view::from_array(#process_chain)                       \
    };

#define RYTHE_DECLARE_PRIVATE_PROCESS_CHAIN(system_name, process_chain)                                                               \
    inline static rythe::core::process_chain_id RYTHE_CONCAT(RYTHE_CONCAT(system_name, _), RYTHE_CONCAT(process_chain, _id)){         \
        .systemId = RYTHE_CONCAT(system_name, _id), .name = rsl::hashed_string_view::from_array(#process_chain)                       \
    };
