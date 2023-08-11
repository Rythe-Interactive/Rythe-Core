#pragma once
#include "../../util/primitives.hpp"

#include "matrix4.hpp"
#include "../quaternion/quaternion.hpp"
#include "../vector/vector.hpp"

#include "../geometric/length.hpp"
#include "../geometric/normalize.hpp"

#include "../util/type_util.hpp"
#include "../util/close_enough.hpp"

namespace rsl::math
{
    template<typename Scalar>
    [[nodiscard]] vector<Scalar, 3> scale(const matrix<Scalar, 4, 4>& mat) noexcept;

    template<typename Scalar>
    [[nodiscard]] vector<Scalar, 3> scale(const matrix<Scalar, 3, 3>& mat) noexcept;

    template<typename Scalar>
    [[nodiscard]] quaternion<Scalar> orientation(const matrix<Scalar, 4, 4>& mat) noexcept;

    template<typename Scalar>
    [[nodiscard]] quaternion<Scalar> orientation(const matrix<Scalar, 3, 3>& mat) noexcept;

    template<typename Scalar>
    [[nodiscard]] constexpr vector<Scalar, 3> translation(const matrix<Scalar, 4, 4>& mat) noexcept;

    template<typename Scalar>
    void decompose(const matrix<Scalar, 4, 4>& mat, vector<Scalar, 3>& scale, quaternion<Scalar>& orientation, vector<Scalar, 3>& translation) noexcept;

    template<typename Scalar>
    void decompose(const matrix<Scalar, 3, 3>& mat, vector<Scalar, 3>& scale, quaternion<Scalar>& orientation) noexcept;

    template<typename Scalar>
    matrix<Scalar, 4, 4> compose(const vector<Scalar, 3>& scale, const quaternion<Scalar>& orientation, const vector<Scalar, 3>& translation) noexcept;

    template<typename Scalar>
    matrix<Scalar, 3, 3> compose(const vector<Scalar, 3>& scale, const quaternion<Scalar>& orientation) noexcept;
}

#include "decompose.inl"
