#pragma once
#include <rsl/type_util>
#include <rsl/primitives>

/**
 * @file pointer.hpp
 */

namespace rythe::core
{
    /**@class pointer
     * @brief Non owning pointer wrapper.
     * @tparam T Type of the underlying pointer.
     */
    template<typename T>
    struct pointer
    {
        T* ptr;

        R_NODISCARD constexpr T* operator->() noexcept { return ptr; }
        R_NODISCARD constexpr const T* operator->() const noexcept { return ptr; }

        R_NODISCARD constexpr T& operator*() noexcept { return *ptr; }
        R_NODISCARD constexpr const T& operator*() const noexcept { return *ptr; }

        R_NODISCARD constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD constexpr operator const T*() const noexcept { return ptr; }
        R_NODISCARD constexpr operator T*() noexcept { return ptr; }

        constexpr pointer& operator=(T* src) noexcept { ptr = src; return *this; }

        R_NODISCARD constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        R_NODISCARD constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

        R_NODISCARD constexpr bool operator==(T* other) const noexcept { return ptr == other; }
        R_NODISCARD constexpr bool operator!=(T* other) const noexcept { return ptr != other; }
        R_NODISCARD constexpr bool operator< (T* other) const noexcept { return ptr < other; }
        R_NODISCARD constexpr bool operator<=(T* other) const noexcept { return ptr <= other; }
        R_NODISCARD constexpr bool operator> (T* other) const noexcept { return ptr > other; }
        R_NODISCARD constexpr bool operator>=(T* other) const noexcept { return ptr >= other; }

        R_NODISCARD constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }

        constexpr pointer& operator++() noexcept { ptr++; return *this; }
        constexpr pointer& operator--() noexcept { ptr--; return *this; }
        constexpr pointer operator++(int) noexcept { return { ++ptr }; }
        constexpr pointer operator--(int) noexcept { return { --ptr }; }
        R_NODISCARD constexpr pointer operator+(rsl::size_type n) const noexcept { return { ptr + n }; }
        R_NODISCARD constexpr pointer operator-(rsl::size_type n) const noexcept { return { ptr - n }; }
        constexpr pointer& operator+=(rsl::size_type n) noexcept { ptr += n; return *this; }
        constexpr pointer& operator-=(rsl::size_type n) noexcept { ptr -= n; return *this; }
    };

    template<>
    struct pointer<void>
    {
        void* ptr;

        R_NODISCARD constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD constexpr operator const void* () const noexcept { return ptr; }
        R_NODISCARD constexpr operator void* () noexcept { return ptr; }

        constexpr pointer& operator=(void* src) noexcept { ptr = src; return *this; }

        R_NODISCARD constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        R_NODISCARD constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

        R_NODISCARD constexpr bool operator==(void* other) const noexcept { return ptr == other; }
        R_NODISCARD constexpr bool operator!=(void* other) const noexcept { return ptr != other; }
        R_NODISCARD constexpr bool operator< (void* other) const noexcept { return ptr < other; }
        R_NODISCARD constexpr bool operator<=(void* other) const noexcept { return ptr <= other; }
        R_NODISCARD constexpr bool operator> (void* other) const noexcept { return ptr > other; }
        R_NODISCARD constexpr bool operator>=(void* other) const noexcept { return ptr >= other; }

        R_NODISCARD constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };

    template<>
    struct pointer<const void>
    {
        const void* ptr;

        R_NODISCARD constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD constexpr operator const void* () const noexcept { return ptr; }

        constexpr pointer& operator=(const void* src) noexcept { ptr = src; return *this; }

        R_NODISCARD constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        R_NODISCARD constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

        R_NODISCARD constexpr bool operator==(void* other) const noexcept { return ptr == other; }
        R_NODISCARD constexpr bool operator!=(void* other) const noexcept { return ptr != other; }
        R_NODISCARD constexpr bool operator< (void* other) const noexcept { return ptr < other; }
        R_NODISCARD constexpr bool operator<=(void* other) const noexcept { return ptr <= other; }
        R_NODISCARD constexpr bool operator> (void* other) const noexcept { return ptr > other; }
        R_NODISCARD constexpr bool operator>=(void* other) const noexcept { return ptr >= other; }

        R_NODISCARD constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };
}
