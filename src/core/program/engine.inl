#pragma once
#include "engine.hpp"

namespace rythe::core
{
    inline rsl::type_map& this_engine::get_context() noexcept
    {
        return get_instance().get_context();
    }

    inline rsl::memory_allocator& this_engine::get_allocator() noexcept
    {
        return get_instance().get_allocator();
    }
}
