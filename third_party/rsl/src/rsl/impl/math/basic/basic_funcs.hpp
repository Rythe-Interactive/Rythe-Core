#pragma once
#include "abs.hpp"
#include "constraint.hpp"
#include "fmod.hpp"
#include "modf.hpp"
#include "round.hpp"


namespace rsl::math
{
    template<typename type, typename valueType = rsl::remove_cvr_t<typename type::Scalar>>
    [[nodiscard]] valueType* value_ptr(type t)
    {
        return t.data;
    }

    template<typename Scalar>
    [[nodiscard]] Scalar radians(Scalar deg)
    {
        return (deg * pi<Scalar>()) / static_cast<Scalar>(180);
    }
}
