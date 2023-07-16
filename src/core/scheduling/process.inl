#include <core/scheduling/process.hpp>
#pragma once

namespace rythe::core::scheduling
{
    template<rsl::size_type charc>
    inline R_ALWAYS_INLINE Process::Process(const char(&name)[charc], rsl::span interval) : m_name(name), m_nameHash(rsl::nameHash<charc>(name))
    {
        setInterval(interval);
    }
}
