#pragma once
#include <rsl/type_util>
#include <rsl/math>
#include <rsl/hash>

#include "core/ecs/handles/entity.hpp"

/**
 * @file component.hpp
 */

namespace rythe::core::ecs
{
    /**@class component_base
     * @brief Shared bass class for component handles.
     */
    struct component_base
    {
    };

    /**@class component
     * @brief Inter frame storable handle to a component. 
     * @tparam component_type Type of component the handle references.
     */
    template<typename component_type>
    struct component : public component_base
    {
        static constexpr rsl::type_hash<component_type> typeId = rsl::make_hash<component_type>();

        entity owner;

        component& operator=(const component_type& src);
        component& operator=(component_type&& src);

        R_NODISCARD operator component_type& ();
        R_NODISCARD operator const component_type& () const;

        R_NODISCARD bool valid() const noexcept;
        R_NODISCARD operator bool() const noexcept;

        R_NODISCARD component_type& operator*();
        R_NODISCARD const component_type& operator*() const;

        R_NODISCARD component_type* operator->();
        R_NODISCARD const component_type* operator->() const;

        bool operator==(const component& other) const noexcept;

        /**@brief Gets a reference to the component the handle references.
         */
        R_NODISCARD component_type& get();
        R_NODISCARD const component_type& get() const;

        /**@brief Destroys the component the handle references.
         */
        void destroy();
    };
}

#if !defined(DOXY_EXCLUDE)
namespace std
{
    template<typename component_type>
    struct hash<rythe::core::ecs::component<component_type>>
    {
        std::size_t operator()(rythe::core::ecs::component<component_type> const& handle) const noexcept
        {
            std::size_t hash = 0;

            rsl::math::detail::hash_combine(hash,
                std::hash<rythe::core::rsl::id_type>{}(handle.owner->id));
            rsl::math::detail::hash_combine(hash,
                rythe::core::typeHash<component_type>());

            return hash;
        }
    };
}
#endif
