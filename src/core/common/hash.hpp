#pragma once
#include <unordered_map>
#include <string_view>

#include <rsl/primitives>

#include <rsl/type_util>
#include <core/common/string_literal.hpp>

namespace rythe::core
{
    constexpr rsl::id_type combine_hash(rsl::id_type seed, rsl::id_type value);

    struct name_hash
    {
        rsl::id_type value = invalid_id;

        constexpr operator rsl::id_type () const noexcept;

        constexpr name_hash() noexcept;

        template<rsl::size_type N>
        constexpr name_hash(const char(&name)[N]) noexcept;

        template<rsl::size_type N>
        constexpr name_hash(const string_literal<N>& name) noexcept;

        constexpr name_hash(rsl::id_type value) noexcept;

        name_hash(const name_hash& src) noexcept;
        name_hash(name_hash&& src) noexcept;

        name_hash& operator=(const name_hash& src) noexcept;
        name_hash& operator=(name_hash&& src) noexcept;
    };

    namespace detail
    {
        static std::unordered_map<rsl::id_type, rsl::id_type> local_to_global;
        static std::unordered_map<rsl::id_type, rsl::id_type> global_to_local;
    }

    rsl::id_type local_cast(rsl::id_type global);
    rsl::id_type global_cast(rsl::id_type local);

    struct type_hash_base
    {
        friend struct type_reference;

        virtual rsl::id_type local() const noexcept RYTHE_PURE;
        virtual std::string_view local_name() const noexcept RYTHE_PURE;
        virtual rsl::id_type global() const noexcept RYTHE_PURE;
        virtual std::string_view global_name() const noexcept RYTHE_PURE;

    protected:
        virtual type_hash_base* copy() const RYTHE_PURE;
    };

    template<typename T>
    struct type_hash : public type_hash_base
    {
        std::string_view name;
        rsl::id_type value = invalid_id;

        constexpr operator rsl::id_type () const noexcept;

        constexpr type_hash() noexcept : value(localTypeHash<T>()), name(localNameOfType<T>()) {}

        type_hash(const type_hash& src) noexcept : value(src.value), name(src.name) {}
        type_hash(type_hash&& src) noexcept : value(src.value), name(src.name) {}

        type_hash& operator=(const type_hash& src) noexcept
        {
            value = src.value;
            name = src.name;
            return *this;
        }

        type_hash& operator=(type_hash&& src) noexcept
        {
            value = src.value;
            name = src.name;
            return *this;
        }

        virtual rsl::id_type local() const noexcept
        {
            return value;
        }

        virtual std::string_view local_name() const noexcept
        {
            return name;
        }

        virtual rsl::id_type global() const noexcept
        {
            if (!detail::local_to_global.count(value))
            {
                auto global = typeHash<T>();
                detail::local_to_global.emplace(value, global);
                detail::global_to_local.emplace(global, value);
            }
            return typeHash<T>();
        }

        virtual std::string_view global_name() const noexcept
        {
            if (!detail::local_to_global.count(value))
            {
                auto global = typeHash<T>();
                detail::local_to_global.emplace(value, global);
                detail::global_to_local.emplace(global, value);
            }
            return nameOfType<T>();
        }

    protected:
        virtual type_hash_base* copy() const
        {
            if (!detail::local_to_global.count(value))
            {
                auto global = typeHash<T>();
                detail::local_to_global.emplace(value, global);
                detail::global_to_local.emplace(global, value);
            }
            return new type_hash();
        }
    };

    RYTHE_CLANG_SUPPRESS_WARNING_PUSH
    RYTHE_GCC_SUPPRESS_WARNING_PUSH
    RYTHE_CLANG_SUPPRESS_WARNING("-Wdelete-abstract-non-virtual-dtor")
    RYTHE_GCC_SUPPRESS_WARNING("-Wdelete-abstract-non-virtual-dtor")

    struct type_reference
    {
    private:
        std::unique_ptr<type_hash_base> value;

    public:
        type_reference() = default;
        type_reference(std::nullptr_t);
        type_reference(const type_hash_base& src);

        type_reference(const type_reference& src);
        type_reference(type_reference&& src);

        type_reference& operator=(const type_reference& src);
        type_reference& operator=(type_reference&& src);

        rsl::id_type local() const;
        rsl::id_type global() const;
        std::string_view local_name() const;
        std::string_view global_name() const;

        operator rsl::id_type() const;
    };

    RYTHE_GCC_SUPPRESS_WARNING_POP
    RYTHE_CLANG_SUPPRESS_WARNING_POP

    namespace detail
    {
        static std::unordered_map<rsl::id_type, type_reference> hash_to_reference;
    }

    type_reference type_ref_cast(rsl::id_type hash);

    template<typename T>
    constexpr type_hash<T> make_hash() noexcept
    {
        return type_hash<T>{};
    }

    template<rsl::size_type N>
    constexpr name_hash make_hash(const string_literal<N>& src) noexcept
    {
        return name_hash{ src };
    }

    namespace literals
    {
        constexpr name_hash operator""_hs(rsl::cstring src);
    }

}

#if !defined(DOXY_EXCLUDE)
namespace std
{
    template<> struct hash<rythe::core::type_reference>
    {
        std::size_t operator()(rythe::core::type_reference const& handle) const noexcept
        {
            return handle.local();
        }
    };
}
#endif

#include <core/common/hash.inl>
