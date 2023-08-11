#pragma once

#include "swizzle_base.hpp"

#define _MATH_SWIZZLE_4_1_(type)\
struct{ type x, y, z, w; };\
struct{ type r, g, b, a; };\
struct{ type s, t, p, q; };\

#define _MATH_SWIZZLE_4_2_(type)\
struct{::rsl::math::swizzle<type, 4, 0, 0> xx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1> xy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2> xz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3> xw;};\
struct{::rsl::math::swizzle<type, 4, 1, 0> yx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1> yy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2> yz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3> yw;};\
struct{::rsl::math::swizzle<type, 4, 2, 0> zx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1> zy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2> zz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3> zw;};\
struct{::rsl::math::swizzle<type, 4, 3, 0> wx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1> wy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2> wz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3> ww;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0> rr;};\
struct{::rsl::math::swizzle<type, 4, 0, 1> rg;};\
struct{::rsl::math::swizzle<type, 4, 0, 2> rb;};\
struct{::rsl::math::swizzle<type, 4, 0, 3> ra;};\
struct{::rsl::math::swizzle<type, 4, 1, 0> gr;};\
struct{::rsl::math::swizzle<type, 4, 1, 1> gg;};\
struct{::rsl::math::swizzle<type, 4, 1, 2> gb;};\
struct{::rsl::math::swizzle<type, 4, 1, 3> ga;};\
struct{::rsl::math::swizzle<type, 4, 2, 0> br;};\
struct{::rsl::math::swizzle<type, 4, 2, 1> bg;};\
struct{::rsl::math::swizzle<type, 4, 2, 2> bb;};\
struct{::rsl::math::swizzle<type, 4, 2, 3> ba;};\
struct{::rsl::math::swizzle<type, 4, 3, 0> ar;};\
struct{::rsl::math::swizzle<type, 4, 3, 1> ag;};\
struct{::rsl::math::swizzle<type, 4, 3, 2> ab;};\
struct{::rsl::math::swizzle<type, 4, 3, 3> aa;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0> ss;};\
struct{::rsl::math::swizzle<type, 4, 0, 1> st;};\
struct{::rsl::math::swizzle<type, 4, 0, 2> sp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3> sq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0> ts;};\
struct{::rsl::math::swizzle<type, 4, 1, 1> tt;};\
struct{::rsl::math::swizzle<type, 4, 1, 2> tp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3> tq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0> ps;};\
struct{::rsl::math::swizzle<type, 4, 2, 1> pt;};\
struct{::rsl::math::swizzle<type, 4, 2, 2> pp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3> pq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0> qs;};\
struct{::rsl::math::swizzle<type, 4, 3, 1> qt;};\
struct{::rsl::math::swizzle<type, 4, 3, 2> qp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3> qq;};\


#define _MATH_SWIZZLE_4_3_(type)\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0> xxx;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1> xxy;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2> xxz;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3> xxw;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0> xyx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1> xyy;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2> xyz;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3> xyw;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0> xzx;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1> xzy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2> xzz;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3> xzw;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0> xwx;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1> xwy;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2> xwz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3> xww;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0> yxx;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1> yxy;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2> yxz;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3> yxw;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0> yyx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1> yyy;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2> yyz;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3> yyw;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0> yzx;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1> yzy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2> yzz;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3> yzw;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0> ywx;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1> ywy;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2> ywz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3> yww;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0> zxx;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1> zxy;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2> zxz;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3> zxw;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0> zyx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1> zyy;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2> zyz;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3> zyw;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0> zzx;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1> zzy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2> zzz;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3> zzw;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0> zwx;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1> zwy;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2> zwz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3> zww;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0> wxx;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1> wxy;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2> wxz;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3> wxw;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0> wyx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1> wyy;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2> wyz;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3> wyw;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0> wzx;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1> wzy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2> wzz;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3> wzw;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0> wwx;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1> wwy;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2> wwz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3> www;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0> rrr;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1> rrg;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2> rrb;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3> rra;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0> rgr;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1> rgg;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2> rgb;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3> rga;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0> rbr;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1> rbg;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2> rbb;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3> rba;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0> rar;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1> rag;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2> rab;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3> raa;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0> grr;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1> grg;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2> grb;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3> gra;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0> ggr;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1> ggg;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2> ggb;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3> gga;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0> gbr;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1> gbg;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2> gbb;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3> gba;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0> gar;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1> gag;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2> gab;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3> gaa;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0> brr;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1> brg;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2> brb;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3> bra;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0> bgr;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1> bgg;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2> bgb;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3> bga;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0> bbr;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1> bbg;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2> bbb;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3> bba;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0> bar;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1> bag;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2> bab;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3> baa;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0> arr;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1> arg;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2> arb;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3> ara;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0> agr;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1> agg;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2> agb;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3> aga;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0> abr;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1> abg;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2> abb;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3> aba;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0> aar;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1> aag;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2> aab;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3> aaa;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0> sss;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1> sst;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2> ssp;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3> ssq;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0> sts;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1> stt;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2> stp;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3> stq;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0> sps;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1> spt;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2> spp;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3> spq;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0> sqs;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1> sqt;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2> sqp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3> sqq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0> tss;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1> tst;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2> tsp;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3> tsq;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0> tts;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1> ttt;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2> ttp;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3> ttq;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0> tps;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1> tpt;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2> tpp;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3> tpq;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0> tqs;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1> tqt;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2> tqp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3> tqq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0> pss;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1> pst;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2> psp;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3> psq;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0> pts;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1> ptt;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2> ptp;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3> ptq;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0> pps;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1> ppt;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2> ppp;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3> ppq;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0> pqs;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1> pqt;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2> pqp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3> pqq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0> qss;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1> qst;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2> qsp;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3> qsq;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0> qts;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1> qtt;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2> qtp;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3> qtq;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0> qps;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1> qpt;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2> qpp;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3> qpq;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0> qqs;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1> qqt;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2> qqp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3> qqq;};\


#define _MATH_SWIZZLE_4_4_(type)\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 0> xxxx;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 1> xxxy;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 2> xxxz;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 3> xxxw;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 0> xxyx;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 1> xxyy;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 2> xxyz;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 3> xxyw;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 0> xxzx;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 1> xxzy;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 2> xxzz;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 3> xxzw;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 0> xxwx;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 1> xxwy;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 2> xxwz;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 3> xxww;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 0> xyxx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 1> xyxy;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 2> xyxz;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 3> xyxw;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 0> xyyx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 1> xyyy;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 2> xyyz;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 3> xyyw;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 0> xyzx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 1> xyzy;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 2> xyzz;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 3> xyzw;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 0> xywx;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 1> xywy;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 2> xywz;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 3> xyww;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 0> xzxx;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 1> xzxy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 2> xzxz;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 3> xzxw;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 0> xzyx;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 1> xzyy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 2> xzyz;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 3> xzyw;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 0> xzzx;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 1> xzzy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 2> xzzz;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 3> xzzw;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 0> xzwx;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 1> xzwy;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 2> xzwz;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 3> xzww;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 0> xwxx;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 1> xwxy;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 2> xwxz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 3> xwxw;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 0> xwyx;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 1> xwyy;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 2> xwyz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 3> xwyw;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 0> xwzx;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 1> xwzy;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 2> xwzz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 3> xwzw;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 0> xwwx;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 1> xwwy;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 2> xwwz;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 3> xwww;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 0> yxxx;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 1> yxxy;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 2> yxxz;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 3> yxxw;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 0> yxyx;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 1> yxyy;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 2> yxyz;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 3> yxyw;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 0> yxzx;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 1> yxzy;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 2> yxzz;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 3> yxzw;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 0> yxwx;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 1> yxwy;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 2> yxwz;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 3> yxww;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 0> yyxx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 1> yyxy;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 2> yyxz;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 3> yyxw;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 0> yyyx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 1> yyyy;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 2> yyyz;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 3> yyyw;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 0> yyzx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 1> yyzy;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 2> yyzz;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 3> yyzw;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 0> yywx;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 1> yywy;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 2> yywz;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 3> yyww;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 0> yzxx;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 1> yzxy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 2> yzxz;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 3> yzxw;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 0> yzyx;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 1> yzyy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 2> yzyz;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 3> yzyw;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 0> yzzx;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 1> yzzy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 2> yzzz;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 3> yzzw;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 0> yzwx;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 1> yzwy;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 2> yzwz;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 3> yzww;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 0> ywxx;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 1> ywxy;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 2> ywxz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 3> ywxw;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 0> ywyx;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 1> ywyy;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 2> ywyz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 3> ywyw;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 0> ywzx;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 1> ywzy;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 2> ywzz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 3> ywzw;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 0> ywwx;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 1> ywwy;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 2> ywwz;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 3> ywww;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 0> zxxx;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 1> zxxy;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 2> zxxz;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 3> zxxw;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 0> zxyx;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 1> zxyy;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 2> zxyz;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 3> zxyw;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 0> zxzx;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 1> zxzy;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 2> zxzz;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 3> zxzw;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 0> zxwx;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 1> zxwy;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 2> zxwz;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 3> zxww;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 0> zyxx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 1> zyxy;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 2> zyxz;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 3> zyxw;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 0> zyyx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 1> zyyy;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 2> zyyz;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 3> zyyw;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 0> zyzx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 1> zyzy;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 2> zyzz;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 3> zyzw;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 0> zywx;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 1> zywy;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 2> zywz;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 3> zyww;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 0> zzxx;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 1> zzxy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 2> zzxz;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 3> zzxw;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 0> zzyx;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 1> zzyy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 2> zzyz;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 3> zzyw;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 0> zzzx;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 1> zzzy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 2> zzzz;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 3> zzzw;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 0> zzwx;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 1> zzwy;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 2> zzwz;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 3> zzww;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 0> zwxx;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 1> zwxy;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 2> zwxz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 3> zwxw;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 0> zwyx;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 1> zwyy;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 2> zwyz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 3> zwyw;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 0> zwzx;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 1> zwzy;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 2> zwzz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 3> zwzw;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 0> zwwx;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 1> zwwy;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 2> zwwz;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 3> zwww;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 0> wxxx;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 1> wxxy;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 2> wxxz;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 3> wxxw;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 0> wxyx;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 1> wxyy;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 2> wxyz;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 3> wxyw;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 0> wxzx;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 1> wxzy;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 2> wxzz;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 3> wxzw;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 0> wxwx;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 1> wxwy;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 2> wxwz;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 3> wxww;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 0> wyxx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 1> wyxy;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 2> wyxz;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 3> wyxw;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 0> wyyx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 1> wyyy;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 2> wyyz;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 3> wyyw;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 0> wyzx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 1> wyzy;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 2> wyzz;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 3> wyzw;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 0> wywx;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 1> wywy;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 2> wywz;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 3> wyww;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 0> wzxx;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 1> wzxy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 2> wzxz;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 3> wzxw;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 0> wzyx;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 1> wzyy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 2> wzyz;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 3> wzyw;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 0> wzzx;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 1> wzzy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 2> wzzz;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 3> wzzw;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 0> wzwx;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 1> wzwy;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 2> wzwz;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 3> wzww;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 0> wwxx;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 1> wwxy;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 2> wwxz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 3> wwxw;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 0> wwyx;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 1> wwyy;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 2> wwyz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 3> wwyw;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 0> wwzx;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 1> wwzy;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 2> wwzz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 3> wwzw;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 0> wwwx;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 1> wwwy;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 2> wwwz;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 3> wwww;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 0> rrrr;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 1> rrrg;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 2> rrrb;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 3> rrra;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 0> rrgr;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 1> rrgg;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 2> rrgb;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 3> rrga;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 0> rrbr;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 1> rrbg;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 2> rrbb;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 3> rrba;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 0> rrar;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 1> rrag;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 2> rrab;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 3> rraa;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 0> rgrr;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 1> rgrg;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 2> rgrb;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 3> rgra;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 0> rggr;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 1> rggg;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 2> rggb;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 3> rgga;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 0> rgbr;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 1> rgbg;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 2> rgbb;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 3> rgba;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 0> rgar;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 1> rgag;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 2> rgab;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 3> rgaa;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 0> rbrr;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 1> rbrg;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 2> rbrb;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 3> rbra;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 0> rbgr;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 1> rbgg;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 2> rbgb;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 3> rbga;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 0> rbbr;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 1> rbbg;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 2> rbbb;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 3> rbba;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 0> rbar;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 1> rbag;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 2> rbab;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 3> rbaa;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 0> rarr;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 1> rarg;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 2> rarb;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 3> rara;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 0> ragr;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 1> ragg;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 2> ragb;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 3> raga;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 0> rabr;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 1> rabg;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 2> rabb;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 3> raba;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 0> raar;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 1> raag;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 2> raab;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 3> raaa;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 0> grrr;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 1> grrg;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 2> grrb;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 3> grra;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 0> grgr;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 1> grgg;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 2> grgb;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 3> grga;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 0> grbr;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 1> grbg;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 2> grbb;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 3> grba;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 0> grar;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 1> grag;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 2> grab;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 3> graa;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 0> ggrr;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 1> ggrg;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 2> ggrb;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 3> ggra;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 0> gggr;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 1> gggg;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 2> gggb;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 3> ggga;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 0> ggbr;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 1> ggbg;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 2> ggbb;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 3> ggba;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 0> ggar;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 1> ggag;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 2> ggab;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 3> ggaa;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 0> gbrr;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 1> gbrg;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 2> gbrb;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 3> gbra;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 0> gbgr;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 1> gbgg;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 2> gbgb;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 3> gbga;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 0> gbbr;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 1> gbbg;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 2> gbbb;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 3> gbba;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 0> gbar;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 1> gbag;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 2> gbab;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 3> gbaa;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 0> garr;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 1> garg;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 2> garb;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 3> gara;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 0> gagr;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 1> gagg;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 2> gagb;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 3> gaga;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 0> gabr;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 1> gabg;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 2> gabb;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 3> gaba;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 0> gaar;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 1> gaag;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 2> gaab;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 3> gaaa;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 0> brrr;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 1> brrg;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 2> brrb;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 3> brra;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 0> brgr;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 1> brgg;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 2> brgb;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 3> brga;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 0> brbr;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 1> brbg;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 2> brbb;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 3> brba;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 0> brar;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 1> brag;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 2> brab;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 3> braa;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 0> bgrr;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 1> bgrg;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 2> bgrb;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 3> bgra;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 0> bggr;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 1> bggg;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 2> bggb;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 3> bgga;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 0> bgbr;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 1> bgbg;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 2> bgbb;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 3> bgba;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 0> bgar;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 1> bgag;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 2> bgab;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 3> bgaa;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 0> bbrr;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 1> bbrg;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 2> bbrb;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 3> bbra;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 0> bbgr;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 1> bbgg;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 2> bbgb;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 3> bbga;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 0> bbbr;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 1> bbbg;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 2> bbbb;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 3> bbba;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 0> bbar;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 1> bbag;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 2> bbab;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 3> bbaa;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 0> barr;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 1> barg;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 2> barb;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 3> bara;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 0> bagr;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 1> bagg;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 2> bagb;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 3> baga;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 0> babr;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 1> babg;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 2> babb;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 3> baba;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 0> baar;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 1> baag;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 2> baab;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 3> baaa;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 0> arrr;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 1> arrg;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 2> arrb;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 3> arra;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 0> argr;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 1> argg;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 2> argb;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 3> arga;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 0> arbr;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 1> arbg;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 2> arbb;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 3> arba;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 0> arar;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 1> arag;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 2> arab;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 3> araa;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 0> agrr;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 1> agrg;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 2> agrb;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 3> agra;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 0> aggr;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 1> aggg;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 2> aggb;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 3> agga;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 0> agbr;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 1> agbg;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 2> agbb;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 3> agba;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 0> agar;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 1> agag;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 2> agab;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 3> agaa;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 0> abrr;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 1> abrg;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 2> abrb;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 3> abra;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 0> abgr;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 1> abgg;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 2> abgb;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 3> abga;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 0> abbr;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 1> abbg;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 2> abbb;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 3> abba;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 0> abar;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 1> abag;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 2> abab;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 3> abaa;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 0> aarr;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 1> aarg;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 2> aarb;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 3> aara;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 0> aagr;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 1> aagg;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 2> aagb;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 3> aaga;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 0> aabr;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 1> aabg;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 2> aabb;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 3> aaba;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 0> aaar;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 1> aaag;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 2> aaab;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 3> aaaa;};\
\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 0> ssss;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 1> ssst;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 2> sssp;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 0, 3> sssq;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 0> ssts;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 1> sstt;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 2> sstp;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 1, 3> sstq;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 0> ssps;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 1> sspt;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 2> sspp;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 2, 3> sspq;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 0> ssqs;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 1> ssqt;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 2> ssqp;};\
struct{::rsl::math::swizzle<type, 4, 0, 0, 3, 3> ssqq;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 0> stss;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 1> stst;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 2> stsp;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 0, 3> stsq;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 0> stts;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 1> sttt;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 2> sttp;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 1, 3> sttq;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 0> stps;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 1> stpt;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 2> stpp;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 2, 3> stpq;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 0> stqs;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 1> stqt;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 2> stqp;};\
struct{::rsl::math::swizzle<type, 4, 0, 1, 3, 3> stqq;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 0> spss;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 1> spst;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 2> spsp;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 0, 3> spsq;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 0> spts;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 1> sptt;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 2> sptp;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 1, 3> sptq;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 0> spps;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 1> sppt;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 2> sppp;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 2, 3> sppq;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 0> spqs;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 1> spqt;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 2> spqp;};\
struct{::rsl::math::swizzle<type, 4, 0, 2, 3, 3> spqq;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 0> sqss;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 1> sqst;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 2> sqsp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 0, 3> sqsq;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 0> sqts;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 1> sqtt;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 2> sqtp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 1, 3> sqtq;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 0> sqps;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 1> sqpt;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 2> sqpp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 2, 3> sqpq;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 0> sqqs;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 1> sqqt;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 2> sqqp;};\
struct{::rsl::math::swizzle<type, 4, 0, 3, 3, 3> sqqq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 0> tsss;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 1> tsst;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 2> tssp;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 0, 3> tssq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 0> tsts;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 1> tstt;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 2> tstp;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 1, 3> tstq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 0> tsps;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 1> tspt;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 2> tspp;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 2, 3> tspq;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 0> tsqs;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 1> tsqt;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 2> tsqp;};\
struct{::rsl::math::swizzle<type, 4, 1, 0, 3, 3> tsqq;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 0> ttss;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 1> ttst;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 2> ttsp;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 0, 3> ttsq;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 0> ttts;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 1> tttt;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 2> tttp;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 1, 3> tttq;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 0> ttps;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 1> ttpt;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 2> ttpp;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 2, 3> ttpq;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 0> ttqs;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 1> ttqt;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 2> ttqp;};\
struct{::rsl::math::swizzle<type, 4, 1, 1, 3, 3> ttqq;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 0> tpss;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 1> tpst;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 2> tpsp;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 0, 3> tpsq;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 0> tpts;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 1> tptt;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 2> tptp;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 1, 3> tptq;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 0> tpps;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 1> tppt;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 2> tppp;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 2, 3> tppq;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 0> tpqs;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 1> tpqt;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 2> tpqp;};\
struct{::rsl::math::swizzle<type, 4, 1, 2, 3, 3> tpqq;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 0> tqss;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 1> tqst;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 2> tqsp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 0, 3> tqsq;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 0> tqts;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 1> tqtt;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 2> tqtp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 1, 3> tqtq;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 0> tqps;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 1> tqpt;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 2> tqpp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 2, 3> tqpq;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 0> tqqs;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 1> tqqt;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 2> tqqp;};\
struct{::rsl::math::swizzle<type, 4, 1, 3, 3, 3> tqqq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 0> psss;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 1> psst;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 2> pssp;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 0, 3> pssq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 0> psts;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 1> pstt;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 2> pstp;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 1, 3> pstq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 0> psps;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 1> pspt;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 2> pspp;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 2, 3> pspq;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 0> psqs;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 1> psqt;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 2> psqp;};\
struct{::rsl::math::swizzle<type, 4, 2, 0, 3, 3> psqq;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 0> ptss;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 1> ptst;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 2> ptsp;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 0, 3> ptsq;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 0> ptts;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 1> pttt;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 2> pttp;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 1, 3> pttq;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 0> ptps;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 1> ptpt;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 2> ptpp;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 2, 3> ptpq;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 0> ptqs;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 1> ptqt;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 2> ptqp;};\
struct{::rsl::math::swizzle<type, 4, 2, 1, 3, 3> ptqq;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 0> ppss;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 1> ppst;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 2> ppsp;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 0, 3> ppsq;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 0> ppts;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 1> pptt;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 2> pptp;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 1, 3> pptq;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 0> ppps;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 1> pppt;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 2> pppp;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 2, 3> pppq;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 0> ppqs;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 1> ppqt;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 2> ppqp;};\
struct{::rsl::math::swizzle<type, 4, 2, 2, 3, 3> ppqq;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 0> pqss;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 1> pqst;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 2> pqsp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 0, 3> pqsq;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 0> pqts;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 1> pqtt;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 2> pqtp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 1, 3> pqtq;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 0> pqps;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 1> pqpt;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 2> pqpp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 2, 3> pqpq;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 0> pqqs;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 1> pqqt;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 2> pqqp;};\
struct{::rsl::math::swizzle<type, 4, 2, 3, 3, 3> pqqq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 0> qsss;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 1> qsst;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 2> qssp;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 0, 3> qssq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 0> qsts;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 1> qstt;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 2> qstp;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 1, 3> qstq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 0> qsps;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 1> qspt;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 2> qspp;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 2, 3> qspq;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 0> qsqs;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 1> qsqt;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 2> qsqp;};\
struct{::rsl::math::swizzle<type, 4, 3, 0, 3, 3> qsqq;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 0> qtss;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 1> qtst;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 2> qtsp;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 0, 3> qtsq;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 0> qtts;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 1> qttt;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 2> qttp;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 1, 3> qttq;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 0> qtps;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 1> qtpt;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 2> qtpp;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 2, 3> qtpq;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 0> qtqs;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 1> qtqt;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 2> qtqp;};\
struct{::rsl::math::swizzle<type, 4, 3, 1, 3, 3> qtqq;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 0> qpss;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 1> qpst;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 2> qpsp;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 0, 3> qpsq;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 0> qpts;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 1> qptt;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 2> qptp;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 1, 3> qptq;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 0> qpps;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 1> qppt;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 2> qppp;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 2, 3> qppq;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 0> qpqs;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 1> qpqt;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 2> qpqp;};\
struct{::rsl::math::swizzle<type, 4, 3, 2, 3, 3> qpqq;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 0> qqss;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 1> qqst;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 2> qqsp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 0, 3> qqsq;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 0> qqts;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 1> qqtt;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 2> qqtp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 1, 3> qqtq;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 0> qqps;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 1> qqpt;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 2> qqpp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 2, 3> qqpq;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 0> qqqs;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 1> qqqt;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 2> qqqp;};\
struct{::rsl::math::swizzle<type, 4, 3, 3, 3, 3> qqqq;};\
