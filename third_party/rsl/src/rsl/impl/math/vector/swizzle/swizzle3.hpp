#pragma once

#include "swizzle_base.hpp"

#define _MATH_SWIZZLE_3_1_(type)\
struct{ type x, y, z; };\
struct{ type u, v, w; };\
struct{ type r, g, b; };\
struct{ type s, t, p; };\

#define _MATH_SWIZZLE_3_2_(type)\
struct{::rsl::math::swizzle<type, 3, 0, 0> xx;};\
struct{::rsl::math::swizzle<type, 3, 0, 1> xy;};\
struct{::rsl::math::swizzle<type, 3, 0, 2> xz;};\
struct{::rsl::math::swizzle<type, 3, 1, 0> yx;};\
struct{::rsl::math::swizzle<type, 3, 1, 1> yy;};\
struct{::rsl::math::swizzle<type, 3, 1, 2> yz;};\
struct{::rsl::math::swizzle<type, 3, 2, 0> zx;};\
struct{::rsl::math::swizzle<type, 3, 2, 1> zy;};\
struct{::rsl::math::swizzle<type, 3, 2, 2> zz;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0> uu;};\
struct{::rsl::math::swizzle<type, 3, 0, 1> uv;};\
struct{::rsl::math::swizzle<type, 3, 0, 2> uw;};\
struct{::rsl::math::swizzle<type, 3, 1, 0> vu;};\
struct{::rsl::math::swizzle<type, 3, 1, 1> vv;};\
struct{::rsl::math::swizzle<type, 3, 1, 2> vw;};\
struct{::rsl::math::swizzle<type, 3, 2, 0> wu;};\
struct{::rsl::math::swizzle<type, 3, 2, 1> wv;};\
struct{::rsl::math::swizzle<type, 3, 2, 2> ww;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0> rr;};\
struct{::rsl::math::swizzle<type, 3, 0, 1> rg;};\
struct{::rsl::math::swizzle<type, 3, 0, 2> rb;};\
struct{::rsl::math::swizzle<type, 3, 1, 0> gr;};\
struct{::rsl::math::swizzle<type, 3, 1, 1> gg;};\
struct{::rsl::math::swizzle<type, 3, 1, 2> gb;};\
struct{::rsl::math::swizzle<type, 3, 2, 0> br;};\
struct{::rsl::math::swizzle<type, 3, 2, 1> bg;};\
struct{::rsl::math::swizzle<type, 3, 2, 2> bb;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0> ss;};\
struct{::rsl::math::swizzle<type, 3, 0, 1> st;};\
struct{::rsl::math::swizzle<type, 3, 0, 2> sp;};\
struct{::rsl::math::swizzle<type, 3, 1, 0> ts;};\
struct{::rsl::math::swizzle<type, 3, 1, 1> tt;};\
struct{::rsl::math::swizzle<type, 3, 1, 2> tp;};\
struct{::rsl::math::swizzle<type, 3, 2, 0> ps;};\
struct{::rsl::math::swizzle<type, 3, 2, 1> pt;};\
struct{::rsl::math::swizzle<type, 3, 2, 2> pp;};\

#define _MATH_SWIZZLE_3_3_(type)\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0> xxx;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1> xxy;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2> xxz;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0> xyx;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1> xyy;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2> xyz;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0> xzx;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1> xzy;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2> xzz;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0> yxx;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1> yxy;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2> yxz;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0> yyx;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1> yyy;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2> yyz;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0> yzx;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1> yzy;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2> yzz;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0> zxx;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1> zxy;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2> zxz;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0> zyx;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1> zyy;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2> zyz;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0> zzx;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1> zzy;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2> zzz;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0> uuu;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1> uuv;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2> uuw;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0> uvu;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1> uvv;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2> uvw;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0> uwu;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1> uwv;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2> uww;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0> vuu;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1> vuv;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2> vuw;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0> vvu;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1> vvv;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2> vvw;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0> vwu;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1> vwv;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2> vww;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0> wuu;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1> wuv;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2> wuw;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0> wvu;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1> wvv;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2> wvw;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0> wwu;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1> wwv;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2> www;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0> rrr;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1> rrg;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2> rrb;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0> rgr;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1> rgg;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2> rgb;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0> rbr;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1> rbg;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2> rbb;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0> grr;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1> grg;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2> grb;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0> ggr;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1> ggg;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2> ggb;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0> gbr;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1> gbg;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2> gbb;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0> brr;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1> brg;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2> brb;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0> bgr;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1> bgg;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2> bgb;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0> bbr;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1> bbg;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2> bbb;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0> sss;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1> sst;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2> ssp;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0> sts;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1> stt;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2> stp;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0> sps;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1> spt;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2> spp;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0> tss;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1> tst;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2> tsp;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0> tts;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1> ttt;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2> ttp;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0> tps;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1> tpt;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2> tpp;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0> pss;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1> pst;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2> psp;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0> pts;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1> ptt;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2> ptp;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0> pps;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1> ppt;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2> ppp;};\

#define _MATH_SWIZZLE_3_4_(type)\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 0> xxxx;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 1> xxxy;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 2> xxxz;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 0> xxyx;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 1> xxyy;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 2> xxyz;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 0> xxzx;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 1> xxzy;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 2> xxzz;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 0> xyxx;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 1> xyxy;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 2> xyxz;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 0> xyyx;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 1> xyyy;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 2> xyyz;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 0> xyzx;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 1> xyzy;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 2> xyzz;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 0> xzxx;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 1> xzxy;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 2> xzxz;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 0> xzyx;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 1> xzyy;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 2> xzyz;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 0> xzzx;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 1> xzzy;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 2> xzzz;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 0> yxxx;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 1> yxxy;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 2> yxxz;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 0> yxyx;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 1> yxyy;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 2> yxyz;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 0> yxzx;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 1> yxzy;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 2> yxzz;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 0> yyxx;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 1> yyxy;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 2> yyxz;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 0> yyyx;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 1> yyyy;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 2> yyyz;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 0> yyzx;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 1> yyzy;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 2> yyzz;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 0> yzxx;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 1> yzxy;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 2> yzxz;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 0> yzyx;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 1> yzyy;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 2> yzyz;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 0> yzzx;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 1> yzzy;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 2> yzzz;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 0> zxxx;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 1> zxxy;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 2> zxxz;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 0> zxyx;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 1> zxyy;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 2> zxyz;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 0> zxzx;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 1> zxzy;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 2> zxzz;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 0> zyxx;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 1> zyxy;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 2> zyxz;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 0> zyyx;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 1> zyyy;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 2> zyyz;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 0> zyzx;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 1> zyzy;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 2> zyzz;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 0> zzxx;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 1> zzxy;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 2> zzxz;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 0> zzyx;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 1> zzyy;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 2> zzyz;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 0> zzzx;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 1> zzzy;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 2> zzzz;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 0> uuuu;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 1> uuuv;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 2> uuuw;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 0> uuvu;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 1> uuvv;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 2> uuvw;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 0> uuwu;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 1> uuwv;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 2> uuww;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 0> uvuu;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 1> uvuv;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 2> uvuw;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 0> uvvu;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 1> uvvv;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 2> uvvw;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 0> uvwu;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 1> uvwv;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 2> uvww;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 0> uwuu;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 1> uwuv;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 2> uwuw;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 0> uwvu;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 1> uwvv;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 2> uwvw;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 0> uwwu;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 1> uwwv;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 2> uwww;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 0> vuuu;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 1> vuuv;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 2> vuuw;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 0> vuvu;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 1> vuvv;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 2> vuvw;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 0> vuwu;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 1> vuwv;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 2> vuww;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 0> vvuu;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 1> vvuv;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 2> vvuw;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 0> vvvu;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 1> vvvv;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 2> vvvw;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 0> vvwu;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 1> vvwv;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 2> vvww;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 0> vwuu;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 1> vwuv;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 2> vwuw;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 0> vwvu;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 1> vwvv;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 2> vwvw;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 0> vwwu;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 1> vwwv;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 2> vwww;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 0> wuuu;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 1> wuuv;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 2> wuuw;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 0> wuvu;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 1> wuvv;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 2> wuvw;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 0> wuwu;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 1> wuwv;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 2> wuww;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 0> wvuu;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 1> wvuv;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 2> wvuw;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 0> wvvu;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 1> wvvv;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 2> wvvw;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 0> wvwu;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 1> wvwv;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 2> wvww;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 0> wwuu;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 1> wwuv;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 2> wwuw;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 0> wwvu;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 1> wwvv;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 2> wwvw;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 0> wwwu;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 1> wwwv;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 2> wwww;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 0> rrrr;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 1> rrrg;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 2> rrrb;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 0> rrgr;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 1> rrgg;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 2> rrgb;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 0> rrbr;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 1> rrbg;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 2> rrbb;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 0> rgrr;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 1> rgrg;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 2> rgrb;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 0> rggr;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 1> rggg;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 2> rggb;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 0> rgbr;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 1> rgbg;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 2> rgbb;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 0> rbrr;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 1> rbrg;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 2> rbrb;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 0> rbgr;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 1> rbgg;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 2> rbgb;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 0> rbbr;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 1> rbbg;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 2> rbbb;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 0> grrr;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 1> grrg;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 2> grrb;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 0> grgr;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 1> grgg;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 2> grgb;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 0> grbr;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 1> grbg;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 2> grbb;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 0> ggrr;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 1> ggrg;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 2> ggrb;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 0> gggr;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 1> gggg;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 2> gggb;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 0> ggbr;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 1> ggbg;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 2> ggbb;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 0> gbrr;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 1> gbrg;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 2> gbrb;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 0> gbgr;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 1> gbgg;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 2> gbgb;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 0> gbbr;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 1> gbbg;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 2> gbbb;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 0> brrr;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 1> brrg;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 2> brrb;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 0> brgr;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 1> brgg;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 2> brgb;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 0> brbr;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 1> brbg;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 2> brbb;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 0> bgrr;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 1> bgrg;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 2> bgrb;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 0> bggr;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 1> bggg;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 2> bggb;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 0> bgbr;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 1> bgbg;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 2> bgbb;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 0> bbrr;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 1> bbrg;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 2> bbrb;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 0> bbgr;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 1> bbgg;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 2> bbgb;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 0> bbbr;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 1> bbbg;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 2> bbbb;};\
\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 0> ssss;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 1> ssst;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 0, 2> sssp;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 0> ssts;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 1> sstt;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 1, 2> sstp;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 0> ssps;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 1> sspt;};\
struct{::rsl::math::swizzle<type, 3, 0, 0, 2, 2> sspp;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 0> stss;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 1> stst;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 0, 2> stsp;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 0> stts;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 1> sttt;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 1, 2> sttp;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 0> stps;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 1> stpt;};\
struct{::rsl::math::swizzle<type, 3, 0, 1, 2, 2> stpp;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 0> spss;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 1> spst;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 0, 2> spsp;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 0> spts;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 1> sptt;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 1, 2> sptp;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 0> spps;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 1> sppt;};\
struct{::rsl::math::swizzle<type, 3, 0, 2, 2, 2> sppp;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 0> tsss;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 1> tsst;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 0, 2> tssp;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 0> tsts;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 1> tstt;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 1, 2> tstp;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 0> tsps;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 1> tspt;};\
struct{::rsl::math::swizzle<type, 3, 1, 0, 2, 2> tspp;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 0> ttss;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 1> ttst;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 0, 2> ttsp;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 0> ttts;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 1> tttt;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 1, 2> tttp;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 0> ttps;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 1> ttpt;};\
struct{::rsl::math::swizzle<type, 3, 1, 1, 2, 2> ttpp;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 0> tpss;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 1> tpst;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 0, 2> tpsp;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 0> tpts;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 1> tptt;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 1, 2> tptp;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 0> tpps;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 1> tppt;};\
struct{::rsl::math::swizzle<type, 3, 1, 2, 2, 2> tppp;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 0> psss;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 1> psst;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 0, 2> pssp;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 0> psts;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 1> pstt;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 1, 2> pstp;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 0> psps;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 1> pspt;};\
struct{::rsl::math::swizzle<type, 3, 2, 0, 2, 2> pspp;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 0> ptss;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 1> ptst;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 0, 2> ptsp;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 0> ptts;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 1> pttt;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 1, 2> pttp;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 0> ptps;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 1> ptpt;};\
struct{::rsl::math::swizzle<type, 3, 2, 1, 2, 2> ptpp;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 0> ppss;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 1> ppst;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 0, 2> ppsp;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 0> ppts;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 1> pptt;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 1, 2> pptp;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 0> ppps;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 1> pppt;};\
struct{::rsl::math::swizzle<type, 3, 2, 2, 2, 2> pppp;};\
