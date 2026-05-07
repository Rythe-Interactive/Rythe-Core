#pragma once
#include "process_context.hpp"

namespace rythe::core
{
    template <rsl::function_ptr ProcessImplType>
    process_context_type<ProcessImplType> untyped_process_context::get_context() noexcept
    {
        process_context_type<ProcessImplType> result;
        result.m_context = { this };
        return result;
    }

    template <rsl::function_ptr ProcessImplType>
    process_function::process_function(process_type type, ProcessImplType impl)
        : type(type),
          func([&](untyped_process_context ctx) { impl(ctx.get_context<ProcessImplType>()); })
    {}
}
