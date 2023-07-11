#pragma once
#include <tuple>
#include <variant>
#include <functional>
#include <type_traits>

#include <rsl/type_util>
#include <rsl/primitives>

#include <core/ecs/handles/entity.hpp>

/**
 * @file archetype.hpp
 */

namespace rythe::core::ecs
{
    template<typename component_type>
    struct component;

    class Registry;

    /**@class archetype_base
     * @brief Common base class of all archetypes. Allows SFINAE checks for whether a templated type is an archetype.
     */
    struct archetype_base {};

    /**@class archetype
     * @brief API object for grouping multiple component types together.
     * @ref rythe::core::transform
     */
    template<typename component_type, typename... component_types>
    struct archetype : public archetype_base
    {
        friend class rythe::core::ecs::Registry;
        friend struct rythe::core::ecs::entity;

        template<typename X, typename... Args>
        friend X& std::get(archetype<Args...>&);

        template<rsl::size_type I, typename Arg, typename... Args>
        friend rsl::element_at_t<I, Arg, Args...>& std::get(archetype<Arg, Args...>&);

    public:
        using handle_group = std::tuple<component<component_type>, component<component_types>...>;
        using const_handle_group = std::tuple<const component<component_type>, const component<component_types>...>;
        using ref_group = std::tuple<component_type&, component_types&...>;
        using copy_group = std::tuple<const component_type&, const component_types&...>;

        entity owner;

        archetype() noexcept = default;
        archetype(const archetype&) noexcept;
        archetype(archetype&&) noexcept;
        archetype(const handle_group& handles) noexcept;

        explicit archetype(const component_type& comp, const component_types&... comps) noexcept;

        archetype& operator=(const archetype& src);
        archetype& operator=(archetype&& src);

        /**@brief Get the handle to one of the components in the archetype.
         */
        template<typename T>
        R_NODISCARD T& get();

        R_NODISCARD ref_group get();

        template<rsl::size_type I>
        R_NODISCARD rsl::element_at_t<I, component_type, component_types...>& get();

        R_NODISCARD handle_group handles();
        R_NODISCARD const_handle_group handles() const;
        R_NODISCARD ref_group values();

        R_NODISCARD bool valid() const;

        R_NODISCARD operator bool() const;

        void destroy();

        R_NODISCARD static handle_group get_handles(entity ent);
        R_NODISCARD static const_handle_group get_const_handles(entity ent);
        R_NODISCARD static ref_group get(entity ent);
        static void destroy(entity ent);
        R_NODISCARD static bool has(entity ent);

    private:
        std::variant<handle_group, copy_group> underlying;

        static ref_group create(entity ent);
        template<typename component_type0, typename... component_typeN>
        static ref_group create(entity ent, component_type0&& value0, component_typeN&&... valueN);
        static ref_group create(entity ent, archetype&& value);
    };

    template<typename component_type, typename... component_types>
    using ar = archetype<component_type, component_types...>;

#if !defined(DOXY_EXCLUDE)
    template<typename component_type, typename... component_types>
    archetype(const std::tuple<component<component_type>, component<component_types>...>&) -> archetype<component_type, component_types...>;

    template<typename component_type, typename... component_types>
    archetype(const component_type&, const component_types&...) -> archetype<component_type, component_types...>;
#endif

    template <class T>
    struct ch_yield_type
    {
    };

    template <class T>
    struct ch_yield_type<component<T>>
    {
        using type = T;
    };

}

namespace std // NOLINT(cert-dcl58-cpp)
{
    template <::std::size_t I, class Arg, class... Args>
    struct tuple_element<I, rythe::core::ecs::archetype<Arg, Args...>>
    {
        using type = typename rsl::element_at_t<I, Arg, Args...>;
    };

    template <::std::size_t I, class Arg, class... Args>
    rsl::element_at_t<I, Arg, Args...>&
        get(rythe::core::ecs::archetype<Arg, Args...>& val)
    {
        return std::get<I>(std::get<0>(val.underlying));
    }

    template <class X, class... Args>
    X& get(rythe::core::ecs::archetype<Args...>& val)
    {
        return std::get<rythe::core::ecs::component<X>>(std::get<0>(val.underlying));
    }

    template <class... Types>
    struct tuple_size<rythe::core::ecs::archetype<Types...>>
        : public std::integral_constant<std::size_t, sizeof...(Types)>
    {
    };
    template <class... Types>
    struct tuple_size<const rythe::core::ecs::archetype<Types...>>
        : public std::integral_constant<std::size_t, sizeof...(Types)>
    {
    };
    template <class... Types>
    struct tuple_size<volatile rythe::core::ecs::archetype<Types...>>
        : public std::integral_constant<std::size_t, sizeof...(Types)>
    {
    };
    template <class... Types>
    struct tuple_size<const volatile rythe::core::ecs::archetype<Types...>>
        : public std::integral_constant<std::size_t, sizeof...(Types)>
    {
    };

}
