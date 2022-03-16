#include "scalar_constants.hpp"

namespace legion::core::math
{
    template<typename T, qualifier Q>
    GLM_FUNC_QUALIFIER T angleOfQuat(qua<T, Q> const& x)
    {
        if (abs(x.w) > cos_one_over_two<T>())
        {
            return asin(sqrt(x.x * x.x + x.y * x.y + x.z * x.z)) * static_cast<T>(2);
        }

        return acos(x.w) * static_cast<T>(2);
    }

    template<typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<3, T, Q> axisOfQuat(qua<T, Q> const& x)
    {
        T const tmp1 = static_cast<T>(1) - x.w * x.w;
        if(tmp1 <= static_cast<T>(0))
            return vec<3, T, Q>(0, 0, 1);
        T const tmp2 = static_cast<T>(1) / sqrt(tmp1);
        return vec<3, T, Q>(x.x * tmp2, x.y * tmp2, x.z * tmp2);
    }

    template<typename T, qualifier Q>
    GLM_FUNC_QUALIFIER qua<T, Q> angleAxis(T const& angle, vec<3, T, Q> const& v)
    {
        T const a(angle);
        T const s = math::sin(a * static_cast<T>(0.5));

        return qua<T, Q>(math::cos(a * static_cast<T>(0.5)), v * s);
    }
}//namespace legion::core::math
