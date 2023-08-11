#pragma once

#include "swizzle_base.hpp"

#define _MATH_SWIZZLE_2_1_(type)\
struct{ type x, y; };\
struct{ type u, v; };\
struct{ type r, g; };\
struct{ type s, t; };\

#define _MATH_SWIZZLE_2_2_(type)\
struct{::rsl::math::swizzle<type, 2, 0, 0> xx;};\
struct{::rsl::math::swizzle<type, 2, 0, 1> xy;};\
struct{::rsl::math::swizzle<type, 2, 1, 0> yx;};\
struct{::rsl::math::swizzle<type, 2, 1, 1> yy;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0> uu;};\
struct{::rsl::math::swizzle<type, 2, 0, 1> uv;};\
struct{::rsl::math::swizzle<type, 2, 1, 0> vu;};\
struct{::rsl::math::swizzle<type, 2, 1, 1> vv;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0> rr;};\
struct{::rsl::math::swizzle<type, 2, 0, 1> rg;};\
struct{::rsl::math::swizzle<type, 2, 1, 0> gr;};\
struct{::rsl::math::swizzle<type, 2, 1, 1> gg;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0> ss;};\
struct{::rsl::math::swizzle<type, 2, 0, 1> st;};\
struct{::rsl::math::swizzle<type, 2, 1, 0> ts;};\
struct{::rsl::math::swizzle<type, 2, 1, 1> tt;};\

#define _MATH_SWIZZLE_2_3_(type)\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0> xxx;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1> xxy;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0> xyx;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1> xyy;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0> yxx;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1> yxy;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0> yyx;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1> yyy;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0> uuu;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1> uuv;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0> uvu;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1> uvv;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0> vuu;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1> vuv;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0> vvu;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1> vvv;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0> rrr;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1> rrg;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0> rgr;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1> rgg;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0> grr;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1> grg;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0> ggr;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1> ggg;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0> sss;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1> sst;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0> sts;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1> stt;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0> tss;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1> tst;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0> tts;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1> ttt;};\

#define _MATH_SWIZZLE_2_4_(type)\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 0> xxxx;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 1> xxxy;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 0> xxyx;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 1> xxyy;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 0> xyxx;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 1> xyxy;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 0> xyyx;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 1> xyyy;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 0> yxxx;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 1> yxxy;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 0> yxyx;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 1> yxyy;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 0> yyxx;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 1> yyxy;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 0> yyyx;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 1> yyyy;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 0> uuuu;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 1> uuuv;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 0> uuvu;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 1> uuvv;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 0> uvuu;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 1> uvuv;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 0> uvvu;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 1> uvvv;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 0> vuuu;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 1> vuuv;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 0> vuvu;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 1> vuvv;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 0> vvuu;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 1> vvuv;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 0> vvvu;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 1> vvvv;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 0> rrrr;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 1> rrrg;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 0> rrgr;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 1> rrgg;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 0> rgrr;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 1> rgrg;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 0> rggr;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 1> rggg;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 0> grrr;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 1> grrg;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 0> grgr;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 1> grgg;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 0> ggrr;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 1> ggrg;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 0> gggr;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 1> gggg;};\
\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 0> ssss;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 0, 1> ssst;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 0> ssts;};\
struct{::rsl::math::swizzle<type, 2, 0, 0, 1, 1> sstt;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 0> stss;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 0, 1> stst;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 0> stts;};\
struct{::rsl::math::swizzle<type, 2, 0, 1, 1, 1> sttt;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 0> tsss;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 0, 1> tsst;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 0> tsts;};\
struct{::rsl::math::swizzle<type, 2, 1, 0, 1, 1> tstt;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 0> ttss;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 0, 1> ttst;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 0> ttts;};\
struct{::rsl::math::swizzle<type, 2, 1, 1, 1, 1> tttt;};\
