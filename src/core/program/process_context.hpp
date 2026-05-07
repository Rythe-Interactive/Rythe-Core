#pragma once

#include "component.hpp"

namespace rythe::core
{
    template <component_api_type...>
    struct reads
    {};

    template <component_api_type...>
    struct writes
    {};

    template <component_api_type...>
    struct emits
    {};

    template <component_api_type...>
    struct destroys
    {};

    template<typename T>
    concept process_action_type = rsl::specialization_of<T, reads> || rsl::specialization_of<T, writes> ||
            rsl::specialization_of<T, emits> || rsl::specialization_of<T, destroys>;

    template <typename Func>
    struct process_func_info;

    template <typename A>
    struct process_func_info<void (*)(A)>
    {
        using context_type = rsl::remove_cvr_t<A>;
        using function_ptr_type = void (*)(A);
    };

    template <typename F, typename A>
    struct process_func_info<void (F::*)(A) const>
    {
        using context_type = rsl::remove_cvr_t<A>;
        using function_ptr_type = void (*)(A);
    };

    template <typename Func>
    struct process_func_info : process_func_info<decltype(&Func::operator())>
    {};

    template <typename Func>
    using process_context_type = process_func_info<Func>::context_type;

    template <process_action_type...>
    class process_context;

    class untyped_process_context
    {
    public:
        template <rsl::function_ptr ProcessImplType>
        [[nodiscard]] [[rythe_always_inline]] process_context_type<ProcessImplType> get_context() noexcept;
    };

    namespace internal
    {
        template <process_action_type T>
        struct _decompose_process_action;

        template <template <typename...> typename ActionType, typename... components>
        struct _decompose_process_action<ActionType<components...>>
        {
            using type = rsl::type_sequence<components...>;
        };

        template <template <typename...> typename ActionType, typename... Actions>
        struct _select_actions :
            rsl::select_from_type_sequence<
                    rsl::type_sequence<rsl::is_specialization<Actions, ActionType>...>,
                    rsl::type_sequence<Actions...>>
        {};

        template <template <typename...> typename ActionType, typename... Actions>
        struct _select_components :
            rsl::combine_type_sequences_from_sequence<rsl::transform_type_sequence_types_t<
                    _decompose_process_action,
                    typename _select_actions<ActionType, Actions...>::type>>
        {};
    } // namespace internal

    template <process_action_type... Actions>
    class process_context
    {
    public:
        using reading_components = internal::_select_components<reads, Actions...>::type;
        using writing_components = internal::_select_components<writes, Actions...>::type;
        using emitting_components = internal::_select_components<emits, Actions...>::type;
        using destroying_components = internal::_select_components<destroys, Actions...>::type;

        template <component_type ComponentType>
        [[nodiscard]] const ComponentType& read();

        template <component_type ComponentType>
        [[nodiscard]] const ComponentType& read(entity ent);

        template <architype_type Architype>
        [[nodiscard]] architype_tuple_t<const Architype> read();

        template <architype_type Architype>
        [[nodiscard]] architype_tuple_t<const Architype> read(entity ent);

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

        rsl::time_span deltaTime;
        rsl::time_span time;

    private:
        rsl::pointer<untyped_process_context> m_context;

        friend class untyped_process_context;
    };

    enum struct [[rythe_closed_enum]] process_type
    {
        sequential,
        parallel,
    };

    struct process_function
    {
        process_function() = default;

        template <rsl::function_ptr ProcessImplType>
        [[rythe_always_inline]] process_function(process_type type, ProcessImplType impl);

        process_type type;
        rsl::delegate<void(untyped_process_context)> func;
    };
}

#include "process_context.inl"
