#include <core/common/hash.hpp>
#pragma once

namespace rythe::core
{
    constexpr name_hash::operator rsl::id_type() const noexcept
    {
        return value;
    }

    template<typename T>
    constexpr type_hash<T>::operator rsl::id_type() const noexcept
    {
        return value;
    }

    constexpr rsl::id_type combine_hash(rsl::id_type seed, rsl::id_type value)
    {
        value += 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed ^ value;
    }

    constexpr name_hash::name_hash() noexcept {}

    constexpr name_hash::name_hash(rsl::id_type val) noexcept
        : value(val) {}

    template<rsl::size_type N>
    inline constexpr name_hash::name_hash(const char(&name)[N]) noexcept
        : value(nameHash<N>(name)) {}

    template<rsl::size_type N>
    inline constexpr name_hash::name_hash(const string_literal<N>& name) noexcept
        : value(nameHash<N>(name)) {}

    constexpr name_hash literals::operator""_hs(rsl::cstring src)
    {
        return name_hash{ nameHash(src) };
    }

}
