#pragma once

#include <string_view>

#include "../util/assert.hpp"
#include "../util/primitives.hpp"

namespace rsl {
    template<size_type maxSize, typename CharType = char>
    struct buffered_string
    {
        using value_type = CharType;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = value_type*;
        using const_iterator = const value_type*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using view_type = std::basic_string_view<value_type>;

    private:
        value_type m_buffer[maxSize + 1];
        size_type m_size;

        constexpr static size_type validate_size(size_type newSize) noexcept { return newSize < maxSize ? newSize : maxSize; }

    public:
        constexpr buffered_string() noexcept = default;

        constexpr buffered_string(const buffered_string& src) noexcept : m_size(validate_size(src.m_size))
        {
            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = src.m_buffer[i];

            m_buffer[m_size] = '\0';
        }

        template<size_type N>
        constexpr buffered_string(const value_type(&str)[N]) noexcept : m_size(validate_size(N))
        {
            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = str[i];

            m_buffer[m_size] = '\0';
        }

        constexpr buffered_string(view_type src) noexcept : m_size(validate_size(src.size()))
        {
            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = src[i];

            m_buffer[m_size] = '\0';
        }

        constexpr buffered_string& operator=(const buffered_string& src) noexcept
        {
            m_size = validate_size(src.m_size);

            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = src.m_buffer[i];

            m_buffer[m_size] = '\0';

            return *this;
        }

        template<size_type N>
        constexpr buffered_string& operator=(const value_type(&str)[N]) noexcept
        {
            m_size = validate_size(N);

            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = str[i];

            m_buffer[m_size] = '\0';

            return *this;
        }

        constexpr buffered_string& operator=(view_type src) noexcept
        {
            m_size = validate_size(src.size());

            for (size_type i = 0; i < m_size; i++)
                m_buffer[i] = src[i];

            m_buffer[m_size] = '\0';

            return *this;
        }

        constexpr reference at(size_type i)
        {
            rsl_assert_msg(i < m_size, "out of range");
            return m_buffer[i];
        }

        constexpr const_reference at(size_type i) const
        {
            rsl_assert_msg(i < m_size, "out of range");
            return m_buffer[i];
        }

        constexpr reference raw_at(size_type i)
        {
            return m_buffer[i];
        }

        constexpr const_reference raw_at(size_type i) const
        {
            return m_buffer[i];
        }

        constexpr reference operator[](size_type i) { return at(i); }
        constexpr const_reference operator[](size_type i) const { return at(i); }

        constexpr bool empty() const noexcept { return m_size == 0; }
        constexpr size_type size() const noexcept { return m_size; }
        constexpr size_type max_size() const noexcept { return maxSize; }

        constexpr void resize(size_type newSize) noexcept {
            size_type oldSize = m_size;
            m_size = validate_size(newSize);

            if (m_size > oldSize) {
                for (size_type i = oldSize; i < m_size; i++)
                    m_buffer[i] = ' ';
            }

            m_buffer[m_size] = '\0';
        }

        constexpr view_type view() const noexcept { return view_type(m_buffer, m_size); }
        constexpr view_type raw_view() const noexcept { return view_type(m_buffer, maxSize); }

        constexpr operator const value_type* () const noexcept { return m_buffer; }
        constexpr operator view_type() const noexcept { return view(); }

        constexpr iterator begin() noexcept { return m_buffer; }
        constexpr const_iterator begin() const noexcept { return m_buffer; }
        constexpr const_iterator cbegin() const noexcept { return m_buffer; }

        constexpr iterator end() noexcept { return &m_buffer[m_size]; }
        constexpr const_iterator end() const noexcept { return &m_buffer[m_size]; }
        constexpr const_iterator cend() const noexcept { return &m_buffer[m_size]; }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(&m_buffer[m_size]); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(&m_buffer[m_size]); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(&m_buffer[m_size]); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(m_buffer); }
        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_buffer); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_buffer); }
    };

    template<size_type maxSize, typename CharType>
    std::ostream& operator<<(std::ostream& os, const buffered_string<maxSize, CharType>& str)
    {
        os << str.view();
        return os;
    }

    template<size_type maxSize, typename CharType>
    buffered_string(const CharType(&)[maxSize]) -> buffered_string<maxSize, CharType>;

    using b_string64 = buffered_string<64>;
    using b_string128 = buffered_string<128>;
    using b_string256 = buffered_string<256>;
    using b_string512 = buffered_string<512>;
}
