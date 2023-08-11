#pragma once
#include <vector>


#include "primitives.hpp"
#include "../defines.hpp"

namespace rsl {
    enum class endian
    {
#ifdef RYTHE_WINDOWS
        little = 0,
        big = 1,
        native = little
#else
        little = __ORDER_LITTLE_ENDIAN__,
        big = __ORDER_BIG_ENDIAN__,
        native = __BYTE_ORDER__
#endif
    };

    template<typename T, typename U>
    constexpr T force_value_cast(U value)
    {
        static_assert(alignof(T) == alignof(U), "Illegal cast of unaligned types.");
        static_assert(sizeof(T) <= sizeof(U), "Illegal cast of non size similar types.");

        return *reinterpret_cast<std::remove_reference_t<T>*>(&value);
    }

    template<typename To, typename From>
    r_always_inline To force_cast(From& f) { return *reinterpret_cast<To*>(&f); }

    template<typename To, typename From>
    r_always_inline const To force_cast(const From& f) { return *reinterpret_cast<const To*>(&f); }
}
