#pragma once
#include "util.hpp"

namespace rsl::math
{
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> perspective(Scalar rads, Scalar aspect, Scalar nearZ, Scalar farZ) noexcept
	{
		Scalar const tanHalfFovy = tan(rads / static_cast<Scalar>(2));

		matrix<Scalar, 4, 4> result(static_cast<Scalar>(0));
		result[0][0] = static_cast<Scalar>(1) / (aspect * tanHalfFovy);
		result[1][1] = static_cast<Scalar>(1) / (tanHalfFovy);
		result[2][2] = (farZ + nearZ) / (farZ - nearZ);
		result[2][3] = static_cast<Scalar>(1);
		result[3][2] = -(static_cast<Scalar>(2) * farZ * nearZ) / (farZ - nearZ);
		return result;
	}

	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> lookAt(vector<Scalar, 3> eye, vector<Scalar, 3> center, vector<Scalar, 3> up) noexcept
	{
		vector<Scalar,3> const f(normalize(center - eye));
		vector<Scalar,3> const s(normalize(cross(f, up)));
		vector<Scalar,3> const u(cross(s, f));

		matrix<Scalar, 4, 4> result(1);
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -dot(s, eye);
		result[3][1] = -dot(u, eye);
		result[3][2] = dot(f, eye);
		return result;
	}

	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> translate(matrix<Scalar, 4, 4> matrix, vector<Scalar, 3> pos) noexcept
	{
		return matrix;
	}
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> rotate(matrix<Scalar, 4, 4> matrix, quaternion<Scalar> orientation) noexcept
	{
		return matrix;
	}
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> rotate(matrix<Scalar, 4, 4> matrix, Scalar rad, vector<Scalar, 3> axis) noexcept
	{
		return matrix;
	}
	template<typename Scalar>
	[[nodiscard]] matrix<Scalar, 4, 4> scale(matrix<Scalar, 4, 4> matrix, vector<Scalar, 3> scale) noexcept
	{
		return matrix;
	}
}