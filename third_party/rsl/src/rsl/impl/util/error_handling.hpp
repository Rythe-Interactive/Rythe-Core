#pragma once

#include <string_view>

#include "../util/primitives.hpp"
#include "../util/concepts.hpp"
#include "../util/assert.hpp"
#include "../containers/buffered_string.hpp"

namespace rsl
{
#if !defined(RSL_ERR_MESSAGE_MAX_LENGTH)
#   define RSL_ERR_MESSAGE_MAX_LENGTH 512
#endif

#if !defined(RSL_WARNING_VALIDATION_LEVEL)
#   define RSL_WARNING_VALIDATION_LEVEL 1
#endif

    template<typename ERRC>
    concept error_type = std::is_enum_v<ERRC> && requires { static_cast<size_type>(std::declval<ERRC>()); };

    template<typename...>
    struct result;

    using errc = int64;

    struct success_type {
        constexpr operator errc() const noexcept { return 0; }
    };

    constexpr static success_type success;

    struct error_context
    {
        thread_local static errc errorCode;
        thread_local static buffered_string<RSL_ERR_MESSAGE_MAX_LENGTH> errorMessage;
    };

    struct error_signal {};

    template<typename T>
    struct result<T> final
    {
    private:
        union
        {
            T m_value;
            byte m_dummy;
        };

    public:
        constexpr result(error_signal) noexcept {}

        template<typename... Args>
        constexpr result(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>) : m_value(std::forward<Args>(args)...) {}

        ~result() {
#if RYTHE_VALIDATION_LEVEL >= RSL_WARNING_VALIDATION_LEVEL

#endif

            rsl_assert_msg(error_context::errorCode == success, error_context::errorMessage);
        }
    };

    template<error_type ErrorType>
    constexpr auto make_error(ErrorType&& errorType, std::string_view message) noexcept
    {
        error_context::errorCode = static_cast<errc>(errorType);
        error_context::errorMessage = message;
        return error_signal{};
    }

    template<typename T, typename... Args>
    constexpr result<T> make_result(Args&&... args) noexcept(std::is_nothrow_constructible_v<result<T>, Args...>)
    {
        return result<T>(std::forward<Args>(args)...);
    }
}
