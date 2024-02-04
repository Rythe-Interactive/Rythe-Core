#pragma once
#include <rsl/primitives>
#include <rsl/type_util>

/**
 * @file pointer.hpp
 */

namespace rythe::core
{
	/**@class pointer
	 * @brief Non owning pointer wrapper.
	 * @tparam T Type of the underlying pointer.
	 */
	template <typename T>
	struct pointer
	{
		T* ptr;

		[[nodiscard]] constexpr T* operator->() noexcept { return ptr; }
		[[nodiscard]] constexpr const T* operator->() const noexcept { return ptr; }

		[[nodiscard]] constexpr T& operator*() noexcept { return *ptr; }
		[[nodiscard]] constexpr const T& operator*() const noexcept { return *ptr; }

		[[nodiscard]] constexpr operator bool() const noexcept { return ptr; }
		[[nodiscard]] constexpr operator const T*() const noexcept { return ptr; }
		[[nodiscard]] constexpr operator T*() noexcept { return ptr; }

		constexpr pointer& operator=(T* src) noexcept
		{
			ptr = src;
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
		[[nodiscard]] constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
		[[nodiscard]] constexpr bool operator<(const pointer& other) const noexcept { return ptr < other.ptr; }
		[[nodiscard]] constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
		[[nodiscard]] constexpr bool operator>(const pointer& other) const noexcept { return ptr > other.ptr; }
		[[nodiscard]] constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

		[[nodiscard]] constexpr bool operator==(T* other) const noexcept { return ptr == other; }
		[[nodiscard]] constexpr bool operator!=(T* other) const noexcept { return ptr != other; }
		[[nodiscard]] constexpr bool operator<(T* other) const noexcept { return ptr < other; }
		[[nodiscard]] constexpr bool operator<=(T* other) const noexcept { return ptr <= other; }
		[[nodiscard]] constexpr bool operator>(T* other) const noexcept { return ptr > other; }
		[[nodiscard]] constexpr bool operator>=(T* other) const noexcept { return ptr >= other; }

		[[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
		[[nodiscard]] constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }

		constexpr pointer& operator++() noexcept
		{
			ptr++;
			return *this;
		}
		constexpr pointer& operator--() noexcept
		{
			ptr--;
			return *this;
		}
		constexpr pointer operator++(int) noexcept { return {++ptr}; }
		constexpr pointer operator--(int) noexcept { return {--ptr}; }
		[[nodiscard]] constexpr pointer operator+(rsl::size_type n) const noexcept { return {ptr + n}; }
		[[nodiscard]] constexpr pointer operator-(rsl::size_type n) const noexcept { return {ptr - n}; }
		constexpr pointer& operator+=(rsl::size_type n) noexcept
		{
			ptr += n;
			return *this;
		}
		constexpr pointer& operator-=(rsl::size_type n) noexcept
		{
			ptr -= n;
			return *this;
		}
	};

	template <>
	struct pointer<void>
	{
		void* ptr;

		[[nodiscard]] constexpr operator bool() const noexcept { return ptr; }
		[[nodiscard]] constexpr operator const void*() const noexcept { return ptr; }
		[[nodiscard]] constexpr operator void*() noexcept { return ptr; }

		constexpr pointer& operator=(void* src) noexcept
		{
			ptr = src;
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
		[[nodiscard]] constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
		[[nodiscard]] constexpr bool operator<(const pointer& other) const noexcept { return ptr < other.ptr; }
		[[nodiscard]] constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
		[[nodiscard]] constexpr bool operator>(const pointer& other) const noexcept { return ptr > other.ptr; }
		[[nodiscard]] constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

		[[nodiscard]] constexpr bool operator==(void* other) const noexcept { return ptr == other; }
		[[nodiscard]] constexpr bool operator!=(void* other) const noexcept { return ptr != other; }
		[[nodiscard]] constexpr bool operator<(void* other) const noexcept { return ptr < other; }
		[[nodiscard]] constexpr bool operator<=(void* other) const noexcept { return ptr <= other; }
		[[nodiscard]] constexpr bool operator>(void* other) const noexcept { return ptr > other; }
		[[nodiscard]] constexpr bool operator>=(void* other) const noexcept { return ptr >= other; }

		[[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
		[[nodiscard]] constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
	};

	template <>
	struct pointer<const void>
	{
		const void* ptr;

		[[nodiscard]] constexpr operator bool() const noexcept { return ptr; }
		[[nodiscard]] constexpr operator const void*() const noexcept { return ptr; }

		constexpr pointer& operator=(const void* src) noexcept
		{
			ptr = src;
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
		[[nodiscard]] constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
		[[nodiscard]] constexpr bool operator<(const pointer& other) const noexcept { return ptr < other.ptr; }
		[[nodiscard]] constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
		[[nodiscard]] constexpr bool operator>(const pointer& other) const noexcept { return ptr > other.ptr; }
		[[nodiscard]] constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

		[[nodiscard]] constexpr bool operator==(void* other) const noexcept { return ptr == other; }
		[[nodiscard]] constexpr bool operator!=(void* other) const noexcept { return ptr != other; }
		[[nodiscard]] constexpr bool operator<(void* other) const noexcept { return ptr < other; }
		[[nodiscard]] constexpr bool operator<=(void* other) const noexcept { return ptr <= other; }
		[[nodiscard]] constexpr bool operator>(void* other) const noexcept { return ptr > other; }
		[[nodiscard]] constexpr bool operator>=(void* other) const noexcept { return ptr >= other; }

		[[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
		[[nodiscard]] constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
	};
} // namespace rythe::core
