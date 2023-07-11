#pragma once
#include <type_traits>
#include <rsl/type_util>
#include <rsl/utilities>

namespace rythe::core::ecs
{
    struct component_base;

    template<typename component_type>
    struct component;

    struct entity;

    struct archetype_base;

    template<typename archetype_type>
    struct is_archetype : std::conditional_t<std::is_base_of_v<archetype_base, rsl::remove_cvr_t<archetype_type>>, std::true_type, std::false_type> {};

    template<typename archetype_type>
    constexpr bool is_archetype_v = is_archetype<archetype_type>::value;

    template<typename component_type>
    struct maybe_component : std::conditional_t<is_archetype_v<component_type>, std::false_type, std::true_type> {};

    template<typename component_type>
    constexpr bool maybe_component_v = maybe_component<component_type>::value;

    HAS_FUNC(init);
    HAS_FUNC(destroy);

    namespace detail
    {
        template<bool,typename>
        struct _wrap_component_impl;

        template<typename component_type>
        struct _wrap_component_impl<true, component_type>
        {
            using type = component<rsl::remove_cvr_t<component_type>>;
        };

        template<typename archetype_type>
        struct _wrap_component_impl<false, archetype_type>
        {
            using type = typename archetype_type::handle_group;
        };

        template<bool,typename>
        struct _const_wrap_component_impl;

        template<typename component_type>
        struct _const_wrap_component_impl<true, component_type>
        {
            using type = const component<rsl::remove_cvr_t<component_type>>;
        };

        template<typename archetype_type>
        struct _const_wrap_component_impl<false, archetype_type>
        {
            using type = typename archetype_type::const_handle_group;
        };

        template<bool, typename>
        struct _component_ref_impl;

        template<typename component_type>
        struct _component_ref_impl<true, component_type>
        {
            using type = rsl::remove_cvr_t<component_type>&;
        };

        template<typename archetype_type>
        struct _component_ref_impl<false, archetype_type>
        {
            using type = typename archetype_type::ref_group;
        };
    }

    template<typename component_type>
    struct wrap_component
    {
        using type = typename detail::_wrap_component_impl<maybe_component_v<component_type>, component_type>::type;
    };

    template<typename component_type>
    using wrap_component_t = typename wrap_component<component_type>::type;

    template<typename component_type>
    struct const_wrap_component
    {
        using type = typename detail::_const_wrap_component_impl<maybe_component_v<component_type>, component_type>::type;
    };

    template<typename component_type>
    using const_wrap_component_t = typename const_wrap_component<component_type>::type;

    template<typename component_type>
    struct component_ref
    {
        using type = typename detail::_component_ref_impl<maybe_component_v<component_type>, component_type>::type;
    };

    template<typename component_type>
    using component_ref_t = typename component_ref<component_type>::type;

    template<typename... component_types>
    using component_tuple = std::tuple<std::conditional_t<maybe_component_v<component_types>, component<rsl::remove_cvr_t<component_types>>, rsl::remove_cvr_t<component_types>>...>;

    template<typename... component_types>
    using const_component_tuple = std::tuple<std::conditional_t<maybe_component_v<component_types>, const component<rsl::remove_cvr_t<component_types>>, const rsl::remove_cvr_t<component_types>>...>;

    template<typename... component_types>
    using component_ref_tuple = std::tuple<component_ref_t<component_types>...>;
}
