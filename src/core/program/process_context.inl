#pragma once
#include "process_context.hpp"

namespace rythe::core
{
    template <rsl::function_ptr ProcessImplType>
    process_context_type<ProcessImplType> untyped_process_context::get_context() noexcept
    {
        process_context_type<ProcessImplType> result;
        result.m_context = { this };
        return result;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    const ComponentType& process_context<Actions...>::read()
    {
        static ComponentType result;
        return result;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    const ComponentType& process_context<Actions...>::read([[maybe_unused]] entity ent)
    {
        static ComponentType result;
        return result;
    }

    namespace internal
    {
        template<typename ProcessContext, typename... Components>
        architype_tuple_t<const architype<Components...>> _multi_read_impl(ProcessContext ctx, rsl::type_sequence<Components...>)
        {
            return rsl::make_tuple(rsl::cref(ctx.template read<Components>())...);
        }

        template <typename ProcessContext, typename... Components>
        architype_tuple_t<const architype<Components...>> _multi_read_impl(ProcessContext ctx, entity ent, rsl::type_sequence<Components...>)
        {
            return rsl::make_tuple(rsl::cref(ctx.template read<Components>(ent))...);
        }
    } // namespace internal

    template <process_action_type... Actions>
    template <component_api_type ComponentTypeOne, component_api_type ComponentTypeTwo, component_api_type... ComponentTypeOthers>
    architype_tuple_t<const architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>> process_context<Actions...>::read()
    {
        return internal::_multi_read_impl(
                    *this,
                    internal::_architype_component_sequence_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>{}
                );
    }

    template <process_action_type... Actions>
    template <component_api_type ComponentTypeOne, component_api_type ComponentTypeTwo, component_api_type... ComponentTypeOthers>
    architype_tuple_t<const architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>
        process_context<Actions...>::read(entity ent)
    {
        return internal::_multi_read_impl(
                    *this,
                    ent,
                    internal::_architype_component_sequence_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>{}
                );
    }

    template <process_action_type... Actions>
    template <architype_type Architype>
    architype_tuple_t<const Architype> process_context<Actions...>::read()
    {
        return internal::_multi_read_impl(*this, internal::_architype_component_sequence_t<internal::_decay_architype_type_t<Architype>>{});
    }

    template <process_action_type... Actions>
    template <architype_type Architype>
    architype_tuple_t<const Architype> process_context<Actions...>::read(entity ent)
    {
        return internal::_multi_read_impl(*this, ent, internal::_architype_component_sequence_t<internal::_decay_architype_type_t<Architype>>{});
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    ComponentType& process_context<Actions...>::write()
    {
        static ComponentType result;
        return result;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    ComponentType& process_context<Actions...>::write([[maybe_unused]] entity ent)
    {
        static ComponentType result;
        return result;
    }

    namespace internal
    {
        template <typename ProcessContext, typename... Components>
        architype_tuple_t<architype<Components...>> _multi_write_impl(ProcessContext ctx, rsl::type_sequence<Components...>)
        {
            return rsl::make_tuple(rsl::ref(ctx.template write<Components>())...);
        }

        template <typename ProcessContext, typename... Components>
        architype_tuple_t<architype<Components...>> _multi_write_impl(ProcessContext ctx, entity ent, rsl::type_sequence<Components...>)
        {
            return rsl::make_tuple(rsl::ref(ctx.template write<Components>(ent))...);
        }
    } // namespace internal

    template <process_action_type... Actions>
    template <component_api_type ComponentTypeOne, component_api_type ComponentTypeTwo, component_api_type... ComponentTypeOthers>
    architype_tuple_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>> process_context<Actions...>::write()
    {
        return internal::_multi_write_impl(
                *this,
                internal::_architype_component_sequence_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>{});
    }

    template <process_action_type... Actions>
    template <component_api_type ComponentTypeOne, component_api_type ComponentTypeTwo, component_api_type... ComponentTypeOthers>
    architype_tuple_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>
            process_context<Actions...>::write(entity ent)
    {
        return internal::_multi_write_impl(
                *this,
                ent,
                internal::_architype_component_sequence_t<architype<ComponentTypeOne, ComponentTypeTwo, ComponentTypeOthers...>>{});
    }

    template <process_action_type... Actions>
    template <architype_type Architype>
    architype_tuple_t<Architype> process_context<Actions...>::write()
    {
        return internal::_multi_write_impl(*this, internal::_architype_component_sequence_t<internal::_decay_architype_type_t<Architype>>{});
    }

    template <process_action_type... Actions>
    template <architype_type Architype>
    architype_tuple_t<Architype> process_context<Actions...>::write(entity ent)
    {
        return internal::_multi_write_impl(*this, ent, internal::_architype_component_sequence_t<internal::_decay_architype_type_t<Architype>>{});
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    ComponentType& process_context<Actions...>::add_component([[maybe_unused]] ComponentType&&)
    {
        static ComponentType result;
        return result;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    ComponentType& process_context<Actions...>::add_component([[maybe_unused]] entity ent, [[maybe_unused]] ComponentType&&)
    {
        static ComponentType result;
        return result;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    bool process_context<Actions...>::remove_component()
    {
        return false;
    }

    template <process_action_type... Actions>
    template <component_type ComponentType>
    bool process_context<Actions...>::remove_component([[maybe_unused]] entity ent)
    {
        return false;
    }

    template <rsl::function_ptr ProcessImplType>
    process_function::process_function(process_type type, ProcessImplType impl)
        : type(type),
          func([&](untyped_process_context ctx) { impl(ctx.get_context<ProcessImplType>()); })
    {}
}
