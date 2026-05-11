#pragma once
#include <rsl/utilities>
#include <rsl/tuple>

namespace rythe::core
{
    struct entity
    {};

    namespace internal
    {
        template <typename Component>
        concept _inclusive_component_type = rsl::standard_layout_type<Component>;
    }

    template <typename... Components>
    struct architype;

    namespace internal
    {
        template <typename... Components>
        architype<Components...> _is_architype_impl(const architype<Components...>&); // NOLINT
    } // namespace internal

    template <typename T, typename = void>
    struct is_architype : rsl::false_type
    {};
    template <typename T>
    struct is_architype<T, rsl::void_t<decltype(internal::_is_architype_impl(T{}))>> : rsl::true_type
    {};

    template <typename T>
    constexpr bool is_architype_v = is_architype<T>::value;

    template <typename Architype>
    concept architype_type = is_architype_v<Architype>;

    template <typename Component>
    concept component_type = internal::_inclusive_component_type<Component> && rsl::invert<architype_type<Component>>;

    template <typename T>
    concept component_api_type = component_type<T> || architype_type<T>;

    template <component_api_type... Components>
    struct architype<Components...>
    {};

    namespace internal
    {
        template<architype_type T>
        struct _decay_architype_type
        {
            using type = decltype(internal::_is_architype_impl(T{}));
        };

        template <architype_type T>
        using _decay_architype_type_t = typename _decay_architype_type<T>::type;

        template <typename T>
        struct _architype_component_sequence;
                
        template <typename T>
        using _architype_component_sequence_t = typename _architype_component_sequence<T>::type;

        template <typename... Components>
        struct _architype_component_sequence<architype<Components...>>
        {
            using type = rsl::combine_type_sequences_from_sequence_t<rsl::type_sequence<_architype_component_sequence_t<Components>...>>;
        };

        template <component_type Component>
        struct _architype_component_sequence<Component>
        {
            using type = rsl::type_sequence<Component>;
        };

        template <architype_type T, bool IsConst>
        struct _architype_tuple_impl;

        template <architype_type T>
        struct _architype_tuple_impl<T, true>
        {
            using type =
                rsl::tuple_from_type_sequence_t<
                    rsl::transform_type_sequence_types_t<
                        rsl::add_lval_ref,
                        rsl::transform_type_sequence_types_t<
                            rsl::add_const,
                            internal::_architype_component_sequence_t<internal::_decay_architype_type_t<T>>
                        >
                    >
                >;
        };

        template <architype_type T>
        struct _architype_tuple_impl<T, false>
        {
            using type =
                rsl::tuple_from_type_sequence_t<
                    rsl::transform_type_sequence_types_t<
                        rsl::add_lval_ref,
                        rsl::transform_type_sequence_types_t<
                            rsl::remove_const,
                            internal::_architype_component_sequence_t<internal::_decay_architype_type_t<T>>
                        >
                    >
                >;
        };
    }

    template <architype_type T>
    struct architype_tuple
    {
        using type = internal::_architype_tuple_impl<T, rsl::is_const_v<T>>::type;
    };

    template <typename T>
    using architype_tuple_t = architype_tuple<T>::type;
}
