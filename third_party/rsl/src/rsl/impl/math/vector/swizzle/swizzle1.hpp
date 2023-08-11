#pragma once

#include "swizzle_base.hpp"

#define _MATH_SWIZZLE_1_1_(type)\
struct{ type x; };\
struct{ type u; };\
struct{ type r; };\
struct{ type s; };\

#define _MATH_SWIZZLE_1_2_(type)\
struct{::rsl::math::swizzle<type, 1, 0, 0> xx;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0> uu;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0> rr;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0> ss;};\

#define _MATH_SWIZZLE_1_3_(type)\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0> xxx;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0> uuu;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0> rrr;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0> sss;};\

#define _MATH_SWIZZLE_1_4_(type)\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0, 0> xxxx;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0, 0> uuuu;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0, 0> rrrr;};\
\
struct{::rsl::math::swizzle<type, 1, 0, 0, 0, 0> ssss;};\
