#include <core/scheduling/processchain.hpp>
#pragma once

namespace rythe::core::scheduling
{
    template<rsl::size_type charc>
    inline rythe_always_inline ProcessChain::ProcessChain(const char(&name)[charc]) : m_name(name), m_nameHash(rsl::nameHash<charc>(name))
    {
    }
}
