#pragma once
#include "../../util/primitives.hpp"

#include "matrix4.hpp"
#include "../quaternion/quaternion.hpp"
#include "../vector/vector.hpp"

#include "../geometric/geometric.hpp"
#include "../trigonometric/trigonometric.hpp"

namespace rsl::math
{
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> perspective(Scalar rads, Scalar fov, Scalar nearZ, Scalar farZ) noexcept;
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> lookAt(vector<Scalar, 3> pos, vector<Scalar, 3> center, vector<Scalar, 3> up) noexcept;

	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> translate(matrix<Scalar, 4, 4> matrix, vector<Scalar, 3> pos) noexcept;
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> rotate(matrix<Scalar, 4, 4> matrix, quaternion<Scalar> orientation) noexcept;
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> rotate(matrix<Scalar, 4, 4> matrix, Scalar rad, vector<Scalar, 3> axis) noexcept;
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> scale(matrix<Scalar, 4, 4> matrix, vector<Scalar, 3> scale) noexcept;
}