#pragma once
/*********************************************************************
 * @file   core/math/util/hash.hpp
 * @date   05-12-2021
 * @brief  Hashing functions and utilities for math structures.
 *
 * Copyright (c) 2021 Rythe-Interactive All rights reserved
 *********************************************************************/

#include <functional>
#include "../../util/primitives.hpp"
#include "../../util/hash.hpp"
#include "../vector/vector.hpp"
#include "../color.hpp"

template<typename Scalar, ::std::size_t Size>
struct ::std::hash<::rsl::math::vector<Scalar, Size>>
{
    constexpr static ::std::hash<Scalar> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::vector<Scalar, Size>& vec) const noexcept
    {
        size_type seed = hasher(vec[0]);
        for (size_type i = 1; i < Size; i++)
            seed = ::rsl::hash_combine(seed, hasher(vec[i]));
        return seed;
    }
};

template<typename Scalar>
struct ::std::hash<::rsl::math::vector<Scalar, 1>>
{
    constexpr static ::std::hash<Scalar> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::vector<Scalar, 1>& vec) const noexcept
    {
        return hasher(vec.x);
    }
};

template<typename Scalar>
struct ::std::hash<::rsl::math::vector<Scalar, 2>>
{
    constexpr static ::std::hash<Scalar> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::vector<Scalar, 2>& vec) const noexcept
    {
        return ::rsl::hash_combine(hasher(vec.x), hasher(vec.y));
    }
};

template<typename Scalar>
struct ::std::hash<::rsl::math::vector<Scalar, 3>>
{
    constexpr static ::std::hash<Scalar> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::vector<Scalar, 3>& vec) const noexcept
    {
        return ::rsl::hash_combine_multiple(hasher(vec.x), hasher(vec.y), hasher(vec.z));
    }
};

template<typename Scalar>
struct ::std::hash<::rsl::math::vector<Scalar, 4>>
{
    constexpr static ::std::hash<Scalar> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::vector<Scalar, 4>& vec) const noexcept
    {
        return ::rsl::hash_combine_multiple(hasher(vec.x), hasher(vec.y), hasher(vec.z), hasher(vec.w));
    }
};

template<>
struct ::std::hash<::rsl::math::color>
{
    constexpr static ::std::hash<rsl::float32> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::color& col) const noexcept
    {
        return ::rsl::hash_combine_multiple(hasher(col.r), hasher(col.g), hasher(col.b), hasher(col.a));
    }
};

template<>
struct ::std::hash<::rsl::math::dcolor>
{
    constexpr static ::std::hash<rsl::float64> hasher{};
    inline r_always_inline::std::size_t operator()(const ::rsl::math::dcolor& col) const noexcept
    {
        return ::rsl::hash_combine_multiple(hasher(col.r), hasher(col.g), hasher(col.b), hasher(col.a));
    }
};

template<typename Scalar, ::std::size_t Size, ::std::size_t... args>
struct ::std::hash<::rsl::math::swizzle<Scalar, Size, args...>>
{
    constexpr static ::std::hash<typename ::rsl::math::swizzle<Scalar, Size, args...>::conv_type> hasher;
    inline r_always_inline::std::size_t operator()(const ::rsl::math::swizzle<Scalar, Size, args...>& vec) const noexcept
    {
        using namespace ::rsl;
        return hasher(vec);
    }
};
