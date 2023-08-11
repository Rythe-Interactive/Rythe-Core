#pragma once

#include <iostream>
#include <cstdlib>

#include "../defines.hpp"

#if defined(RYTHE_VALIDATE)

#define __rsl_assert_impl(expr, file, line, msg)                                                                                \
{                                                                                                                               \
    std::cerr << "Assertion failed:\t" << msg << "\nExpected:\t\t" expr "\nSource:\t\t\t" file ", line " STRINGIFY(line) "\n";  \
    std::abort();                                                                                                               \
}                                                                                                                               \

#define rsl_assert(expr) { if (!!!(expr)) __rsl_assert_impl(#expr, __FILE__, __LINE__, "") }
#define rsl_assert_msg(expr, msg) { if (!!!(expr)) __rsl_assert_impl(#expr, __FILE__, __LINE__, msg) }

#else

#define rsl_assert(expr) if constexpr (false) { [[maybe_unused]] bool b = static_cast<bool>(expr); }
#define rsl_assert_msg(expr, msg) if constexpr (false) { [[maybe_unused]] bool b = static_cast<bool>(expr); [[maybe_unused]] const char* m = static_cast<const char*>(msg); }

#endif
