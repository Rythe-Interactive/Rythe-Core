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

        R_NODISCARD static entity_set::iterator begin() noexcept;
        R_NODISCARD static entity_set::iterator end() noexcept;
        R_NODISCARD static entity_set::reverse_iterator rbegin() noexcept;
        R_NODISCARD static entity_set::reverse_iterator rend() noexcept;
        R_NODISCARD static entity_set::reverse_itr_range reverse_range() noexcept;

        R_NODISCARD static rsl::size_type size() noexcept;
        R_NODISCARD static bool empty() noexcept;

        R_NODISCARD static rsl::size_type count(entity val);
        R_NODISCARD static rsl::size_type contains(entity val);

        R_NODISCARD static entity_set::iterator find(entity val);

        R_NODISCARD static entity& at(rsl::size_type index);
        R_NODISCARD entity& operator[](rsl::size_type index);

        template<typename component_type>
        R_NODISCARD static component_container<component_type>& get();
    };
}

#include <core/ecs/handles/filter.inl>
