#include <core/ecs/filters/filter_info.hpp>
#pragma once

namespace rythe::core::ecs
{
    template<typename... component_types>
    inline rythe_always_inline rsl::id_type filter_info<component_types...>::id()
    {
        return filter_id;
    }

    template<typename... component_types>
    inline rythe_always_inline bool filter_info<component_types...>::contains(rsl::id_type id) noexcept
    {
        return contains_direct(id);
    }

    template<typename... component_types>
    inline rythe_always_inline bool filter_info<component_types...>::contains(const std::unordered_set<rsl::id_type>& comp)
    {
        if (!comp.size())
            return false;

        if (!composition.size())
            return true;

        for (auto& typeId : composition)
            if (!comp.count(typeId))
                return false;
        return true;
    }

    template<typename... component_types>
    constexpr bool filter_info<component_types...>::contains_direct(rsl::id_type id) noexcept
    {
        for (int i = 0; i < composition.size(); i++)
            if (composition[i] == id)
                return true;
        return false;
    }
}
