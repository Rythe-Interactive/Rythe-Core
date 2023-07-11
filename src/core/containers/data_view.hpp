#pragma once
#include <vector>
#include <array>
#include <utility>

#include <rsl/type_util>
#include <rsl/primitives>

#include <core/containers/pointer.hpp>

/**
 * @file data_view.hpp
 */

namespace rythe::core
{
    /**@class data_view
     * @brief Non owning view into an array, vector, or other contiguous data grouping
     * @tparam DataType the value-type of the target data
     */
    template<typename DataType>
    struct data_view
    {
    public:
        using value_type = DataType;
        using iterator = DataType*;

        using ptr_type = DataType*;
        using const_ptr_type = const DataType*;

        using const_value_type = const DataType;
        using const_iterator = const DataType*;

        data_view() noexcept;
        data_view(std::nullptr_t) noexcept;

        explicit data_view(std::vector<value_type>& vec, rsl::diff_type offset = 0);

        template<rsl::size_type N>
        explicit data_view(std::array<value_type, N>& arr, rsl::diff_type offset = 0);

        template<typename Traits, typename Allocator>
        explicit data_view(std::basic_string<DataType, Traits, Allocator>& str, rsl::diff_type offset = 0);

        data_view(ptr_type ptr, rsl::size_type size, rsl::diff_type offset = 0) noexcept;

        data_view(const data_view& other) noexcept;

        data_view(data_view&& other) noexcept;

        data_view& operator=(const data_view& other) noexcept;

        data_view& operator=(data_view&& other) noexcept;

        R_NODISCARD operator bool() const noexcept;

        R_NODISCARD bool operator==(const data_view& other) const noexcept;
        R_NODISCARD bool operator!=(const data_view& other) const noexcept;

        /**@brief gets reference to the value at index idx
         * checks if the index is valid before returning and throws and std::out_of_range exception if it is not
         * @param idx the index to query
         * @returns reference to the value at idx
         */
        R_NODISCARD value_type& at(rsl::size_type idx);

        /**@brief gets const reference to the value at index idx
         * checks if the index is valid before returning and throws and std::out_of_range exception if it is not
         * @param idx the index to query
         * @returns const reference to the value at idx
         */
        R_NODISCARD const value_type& at(rsl::size_type idx) const;

        /**@brief gets reference to the value at index idx
         * @param idx the index to query
         * @returns reference to the value at idx
         */
        value_type& operator[](rsl::size_type idx);

        /**@brief gets const reference to the value at index idx
         * @param idx the index to query
         * @returns const reference to the value at idx
         */
        R_NODISCARD const value_type& operator[](rsl::size_type idx) const;

        R_NODISCARD iterator begin() noexcept;

        R_NODISCARD iterator end() noexcept;

        R_NODISCARD ptr_type data() noexcept;

        R_NODISCARD const_iterator begin() const noexcept;

        R_NODISCARD const_iterator end() const noexcept;

        R_NODISCARD const_ptr_type data() const noexcept;

        /**@brief gets the size of the target data in item count.
         */
        R_NODISCARD rsl::size_type size() const noexcept;

        R_NODISCARD rsl::diff_type offset() const noexcept;

        /**@brief gets the max size this container could grow to.
         * since the container is non resizable same as size()
         */
        R_NODISCARD rsl::size_type max_size() const noexcept;

    private:
        ptr_type m_data;
        rsl::diff_type m_offset;
        rsl::size_type m_size;
    };

    template<>
    struct data_view<void> : public pointer<void>
    {
        data_view() noexcept : pointer<void>({ nullptr }) {}
        data_view(std::nullptr_t) noexcept : pointer<void>({ nullptr }) {}
        data_view(void* src) noexcept : pointer<void>({ src }) {}

        data_view(const data_view& other) noexcept : pointer<void>({ other.ptr }) {}
        data_view(data_view&& other) noexcept : pointer<void>({ other.ptr }) {}

        data_view& operator=(const data_view& other) noexcept
        {
            ptr = other.ptr;
            return *this;
        }

        data_view& operator=(data_view&& other) noexcept
        {
            ptr = other.ptr;
            return *this;
        }

        R_NODISCARD void* data() noexcept { return ptr; }
        R_NODISCARD const void* data() const noexcept { return ptr; }
    };

    template<>
    struct data_view<const void> : public pointer<const void>
    {
        data_view() noexcept : pointer<const void>({ nullptr }) {}
        data_view(std::nullptr_t) noexcept : pointer<const void>({ nullptr }) {}
        data_view(const void* src) noexcept : pointer<const void>({ src }) {}

        data_view(const data_view& other) noexcept : pointer<const void>({ other.ptr }) {}
        data_view(data_view&& other) noexcept : pointer<const void>({ other.ptr }) {}

        data_view& operator=(const data_view& other) noexcept
        {
            ptr = other.ptr;
            return *this;
        }

        data_view& operator=(data_view&& other) noexcept
        {
            ptr = other.ptr;
            return *this;
        }

        R_NODISCARD const void* data() const noexcept { return ptr; }
    };
}

#include <core/containers/data_view.inl>
