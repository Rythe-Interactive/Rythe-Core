#pragma once
#include <vector>
#include <functional>

namespace rythe::core::ecs
{
    template<typename component_type>
    using component_container = std::vector<std::reference_wrapper<component_type>>;
}
