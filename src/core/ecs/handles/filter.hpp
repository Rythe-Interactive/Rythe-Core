#pragma once

#include <rsl/type_util>

#include <core/ecs/handles/entity.hpp>
#include <core/ecs/containers/component_container.hpp>
#include <core/ecs/filters/filterregistry.hpp>
#include <core/ecs/containers/component_pool.hpp>

namespace rythe::core::ecs
{
    template<typename... component_types>
    struct filter
    {
    private:
        static std::tuple<component_container<component_types>...> m_containers;

    public:
        static const rsl::id_type id;

        L_NODISCARD static entity_set::iterator begin() noexcept;
        L_NODISCARD static entity_set::iterator end() noexcept;
        L_NODISCARD static entity_set::reverse_iterator rbegin() noexcept;
        L_NODISCARD static entity_set::reverse_iterator rend() noexcept;
        L_NODISCARD static entity_set::reverse_itr_range reverse_range() noexcept;

        L_NODISCARD static rsl::size_type size() noexcept;
        L_NODISCARD static bool empty() noexcept;

        L_NODISCARD static rsl::size_type count(entity val);
        L_NODISCARD static rsl::size_type contains(entity val);

        L_NODISCARD static entity_set::iterator find(entity val);

        L_NODISCARD static entity& at(rsl::size_type index);
        L_NODISCARD entity& operator[](rsl::size_type index);

        template<typename component_type>
        L_NODISCARD static component_container<component_type>& get();
    };
}

#include <core/ecs/handles/filter.inl>
