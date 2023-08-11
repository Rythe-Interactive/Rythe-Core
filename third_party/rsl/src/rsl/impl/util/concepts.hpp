#pragma once
#include <concepts>

#include "type_util.hpp"

namespace rsl
{
    template<typename Func>
    concept invocable = is_invocable_v<Func>;

    template<typename Func>
    concept function_ptr = is_function_ptr_v<Func>;

    template<typename Func>
    concept functor = is_functor_v<Func>;

    template<typename Func>
    concept member_function_ptr = std::is_member_function_pointer_v<Func>;

    template<typename Type>
    concept ratio_type = is_ratio_v<Type>;

    template<typename Type, template<typename...> typename Template>
    concept specialization_of = is_specialization_v<Type, Template>;
}
