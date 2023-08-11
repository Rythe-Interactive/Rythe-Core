#include "perlin.hpp"
#pragma once

namespace rsl::math
{
    namespace detail
    {
        template<typename scalar>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_1d_impl_(scalar value) noexcept
        {

        }

        template<typename scalar>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_1d_impl_(scalar value, scalar& derivative) noexcept
        {

        }

        template<typename scalar, typename VectorType>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_2d_impl_(VectorType value) noexcept
        {
            //using scalar2 = vector<scalar, 2>;

            //int2 floored = ifloor<int32>(value);

            //int32v x0 = FS_Convertf32_i32(xs) * int32v(FnPrimes::X);
            //int32v y0 = FS_Convertf32_i32(ys) * int32v(FnPrimes::Y);
            //int32v x1 = x0 + int32v(FnPrimes::X);
            //int32v y1 = y0 + int32v(FnPrimes::Y);

            //float32v xf0 = xs = x - xs;
            //float32v yf0 = ys = y - ys;
            //float32v xf1 = xf0 - float32v(1);
            //float32v yf1 = yf0 - float32v(1);

            //xs = FnUtils::InterpQuintic(xs);
            //ys = FnUtils::InterpQuintic(ys);

            //return float32v(0.579106986522674560546875f) * FnUtils::Lerp(
            //    FnUtils::Lerp(FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x0, y0), xf0, yf0), FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x1, y0), xf1, yf0), xs),
            //    FnUtils::Lerp(FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x0, y1), xf0, yf1), FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x1, y1), xf1, yf1), xs), ys);

        }

        template<typename scalar, typename VectorType>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_2d_impl_(VectorType value, vector<scalar, 2>& derivative) noexcept
        {
            //using scalar2 = vector<scalar, 2>;

            //int2 floored = ifloor<int32>(value);

            //int32v x0 = FS_Convertf32_i32(xs) * int32v(FnPrimes::X);
            //int32v y0 = FS_Convertf32_i32(ys) * int32v(FnPrimes::Y);
            //int32v x1 = x0 + int32v(FnPrimes::X);
            //int32v y1 = y0 + int32v(FnPrimes::Y);

            //float32v xf0 = xs = x - xs;
            //float32v yf0 = ys = y - ys;
            //float32v xf1 = xf0 - float32v(1);
            //float32v yf1 = yf0 - float32v(1);

            //xs = FnUtils::InterpQuintic(xs);
            //ys = FnUtils::InterpQuintic(ys);

            //return float32v(0.579106986522674560546875f) * FnUtils::Lerp(
            //    FnUtils::Lerp(FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x0, y0), xf0, yf0), FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x1, y0), xf1, yf0), xs),
            //    FnUtils::Lerp(FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x0, y1), xf0, yf1), FnUtils::GetGradientDot(FnUtils::HashPrimes(seed, x1, y1), xf1, yf1), xs), ys);

        }

        template<typename scalar, typename VectorType>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_3d_impl_(VectorType value) noexcept
        {
            //const auto floored = ifloor<int32>(value);
            //const auto iv = vector<scalar, 3>(floored.x & 255, floored.y & 255, floored.z & 255);
            //const auto fv = value - floored;

            //const auto coords = smoothstep(fv);
            //const auto coordsDerivative = smoothstep_derivative(fv);

            //const uint8 A = (_perlin_permutation_[iv.x & 255] + iv.y) & 255;
            //const uint8 B = (_perlin_permutation_[(iv.x + 1) & 255] + iv.y) & 255;

            //const uint8 AA = (_perlin_permutation_[A] + iv.z) & 255;
            //const uint8 AB = (_perlin_permutation_[(A + 1) & 255] + iv.z) & 255;

            //const uint8 BA = (_perlin_permutation_[B] + iv.z) & 255;
            //const uint8 BB = (_perlin_permutation_[(B + 1) & 255] + iv.z) & 255;

            //const auto p0 = _grad_impl_(_perlin_permutation_[AA], fv.x, fv.y, fv.z);
            //const auto p1 = _grad_impl_(_perlin_permutation_[BA], fv.x - 1, fv.y, fv.z);
            //const auto p2 = _grad_impl_(_perlin_permutation_[AB], fv.x, fv.y - 1, fv.z);
            //const auto p3 = _grad_impl_(_perlin_permutation_[BB], fv.x - 1, fv.y - 1, fv.z);
            //const auto p4 = _grad_impl_(_perlin_permutation_[(AA + 1) & 255], fv.x, fv.y, fv.z - 1);
            //const auto p5 = _grad_impl_(_perlin_permutation_[(BA + 1) & 255], fv.x - 1, fv.y, fv.z - 1);
            //const auto p6 = _grad_impl_(_perlin_permutation_[(AB + 1) & 255], fv.x, fv.y - 1, fv.z - 1);
            //const auto p7 = _grad_impl_(_perlin_permutation_[(BB + 1) & 255], fv.x - 1, fv.y - 1, fv.z - 1);

            //const auto q0 = lerp(p0, p1, u);
            //const auto q1 = lerp(p2, p3, u);
            //const auto q2 = lerp(p4, p5, u);
            //const auto q3 = lerp(p6, p7, u);

            //const auto r0 = lerp(q0, q1, v);
            //const auto r1 = lerp(q2, q3, v); 

            //return perlin_detail::Lerp(r0, r1, w);
        }

        template<typename scalar, typename VectorType>
        [[nodiscard]] r_always_inline constexpr scalar _perlin_3d_impl_(VectorType value, vector<scalar, 3>& derivative) noexcept
        {
            //const auto floored = ifloor<int32>(value);
            //const auto iv = vector<scalar, 3>(floored.x & 255, floored.y & 255, floored.z & 255);
            //const auto fv = value - floored;

            //const auto coords = smoothstep(fv);
            //const auto coordsDerivative = smoothstep_derivative(fv);

            //const uint8 A = (_perlin_permutation_[iv.x & 255] + iv.y) & 255;
            //const uint8 B = (_perlin_permutation_[(iv.x + 1) & 255] + iv.y) & 255;

            //const uint8 AA = (_perlin_permutation_[A] + iv.z) & 255;
            //const uint8 AB = (_perlin_permutation_[(A + 1) & 255] + iv.z) & 255;

            //const uint8 BA = (_perlin_permutation_[B] + iv.z) & 255;
            //const uint8 BB = (_perlin_permutation_[(B + 1) & 255] + iv.z) & 255;

            //const auto p0 = _grad_impl_(_perlin_permutation_[AA], fv.x, fv.y, fv.z);
            //const auto p1 = _grad_impl_(_perlin_permutation_[BA], fv.x - 1, fv.y, fv.z);
            //const auto p2 = _grad_impl_(_perlin_permutation_[AB], fv.x, fv.y - 1, fv.z);
            //const auto p3 = _grad_impl_(_perlin_permutation_[BB], fv.x - 1, fv.y - 1, fv.z);
            //const auto p4 = _grad_impl_(_perlin_permutation_[(AA + 1) & 255], fv.x, fv.y, fv.z - 1);
            //const auto p5 = _grad_impl_(_perlin_permutation_[(BA + 1) & 255], fv.x - 1, fv.y, fv.z - 1);
            //const auto p6 = _grad_impl_(_perlin_permutation_[(AB + 1) & 255], fv.x, fv.y - 1, fv.z - 1);
            //const auto p7 = _grad_impl_(_perlin_permutation_[(BB + 1) & 255], fv.x - 1, fv.y - 1, fv.z - 1);

            //const auto q0 = lerp(p0, p1, u);
            //const auto q1 = lerp(p2, p3, u);
            //const auto q2 = lerp(p4, p5, u);
            //const auto q3 = lerp(p6, p7, u);

            //const auto r0 = lerp(q0, q1, v);
            //const auto r1 = lerp(q2, q3, v); 

            //return perlin_detail::Lerp(r0, r1, w);
        }
    }

    template<typename VectorType>
    [[nodiscard]] r_always_inline constexpr auto perlin(VectorType&& value, int_least<sizeof(vector_scalar_t<VectorType>)> seed) noexcept
    {
        constexpr size_type dimensions = make_vector_t<VectorType>::size;
        //using scalar = typename make_vector_t<VectorType>::scalar;
        static_assert(is_vector_or_scalar_v<VectorType> && make_vector_t<VectorType>::size <= 3, "Input type must be a vector of size 3 or lower.");
        if constexpr (dimensions == 1)
            return detail::_perlin_1d_impl_(value);
        else if constexpr (dimensions == 2)
            return detail::_perlin_2d_impl_(::std::forward<VectorType>(value));
        else if constexpr (dimensions == 3)
            return detail::_perlin_3d_impl_(::std::forward<VectorType>(value));
        else
            return typename make_vector_t<VectorType>::scalar{};
    }

    template<typename VectorType>
    [[nodiscard]] r_always_inline constexpr auto perlin(VectorType&& value, decay_vector_t<VectorType>& derivative, int_least<sizeof(vector_scalar_t<VectorType>)> seed) noexcept
    {
        constexpr size_type dimensions = make_vector_t<VectorType>::size;
        //using scalar = typename make_vector_t<VectorType>::scalar;
        static_assert(is_vector_or_scalar_v<VectorType> && make_vector_t<VectorType>::size <= 3, "Input type must be a vector of size 3 or lower.");
        if constexpr (dimensions == 1)
            return detail::_perlin_1d_impl_(value, derivative);
        else if constexpr (dimensions == 2)
            return detail::_perlin_2d_impl_(::std::forward<VectorType>(value), derivative);
        else if constexpr (dimensions == 3)
            return detail::_perlin_3d_impl_(::std::forward<VectorType>(value), derivative);
        else
            return typename make_vector_t<VectorType>::scalar{};
    }
}
