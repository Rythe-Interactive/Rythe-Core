#pragma once
#include <rsl/utilities>

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
        rsl::tuple<Components&...> _get_architype_impl(architype<Components...>&); // NOLINT
        template <typename... Components>
        rsl::tuple<const Components&...> _get_architype_impl(const architype<Components...>&); // NOLINT
    } // namespace internal

    template <typename T, typename = void>
    struct is_architype : rsl::false_type
    {};
    template <typename T>
    struct is_architype<T, rsl::void_t<decltype(internal::_get_architype_impl(T{}))>> : rsl::true_type
    {};

    template <typename T>
    constexpr bool is_architype_v = is_architype<T>::value;

    template <typename Architype>
    concept architype_type = is_architype_v<Architype>;

    template <architype_type T>
    struct architype_tuple
    {
        using type = decltype(internal::_get_architype_impl(T{}));
    };

    template <typename T>
    using architype_tuple_t = architype_tuple<T>::type;

    template <typename Component>
    concept component_type = internal::_inclusive_component_type<Component> && rsl::invert<architype_type<Component>>;

    template <component_type... Components>
    struct architype<Components...> {};


    template <typename T>
    concept component_api_type = component_type<T> || architype_type<T>;
}
