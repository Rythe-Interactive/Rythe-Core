#pragma once
#include <utility>
#include <ratio>
#include <concepts>

#include "../defines.hpp"
#include "primitives.hpp"
#include "string_util.hpp"

namespace rsl {
    template<template<typename...>typename T, typename U, size_type I, typename... Args>
    struct make_sequence : make_sequence<T, U, I - 1, Args..., U> {};

    template<template<typename...>typename T, typename U, typename... Args>
    struct make_sequence<T, U, 0, Args...> {
        using type = T<Args...>;
    };

    template<template<typename...>typename T, typename U, size_type I, typename... Args>
    using make_sequence_t = typename make_sequence<T, U, I, Args...>::type;

    template<typename Type, template<typename...> typename Template>
    constexpr bool is_specialization_v = false; // true if and only if Type is a specialization of Template
    template<template<typename...> typename Template, typename... Types>
    constexpr bool is_specialization_v<Template<Types...>, Template> = true;

    template<typename Type, template<typename...> typename Template>
    struct is_specialization : std::bool_constant<is_specialization_v<Type, Template>> {};

    template<typename... Types>
    struct type_sequence {
        using tuple_type = std::tuple<Types...>;
        constexpr static size_type size = sizeof...(Types);
    };

    template<typename T>
    concept type_sequence_c = is_specialization_v<T, type_sequence>;

    template<typename...>
    struct concat_sequence;

    template<typename... A, typename... B, type_sequence_c C, type_sequence_c... Rest>
    struct concat_sequence<type_sequence<A...>, type_sequence<B...>, C, Rest...> {
        using type = typename concat_sequence<type_sequence<A..., B...>, C, Rest...>::type;
    };

    template<typename... A, typename... B>
    struct concat_sequence<type_sequence<A...>, type_sequence<B...>> {
        using type = type_sequence<A..., B...>;
    };

    template<type_sequence_c... Sequences>
    using concat_sequence_t = typename concat_sequence<Sequences...>::type;

    template<type_sequence_c Sequence, typename T>
    struct type_sequence_contains;

    template<typename... Types, typename T>
    struct type_sequence_contains<type_sequence<Types...>, T> : std::disjunction<std::is_same<T, Types>...> {};

    template<type_sequence_c Sequence, typename T>
    constexpr bool type_sequence_contains_v = type_sequence_contains<Sequence, T>::value;

    namespace internal {
        struct any_type {
            template<typename T>
            constexpr operator T(); // implicit conversion to any type.
        };

        template<typename Func, size_type... paramCounts>
        constexpr bool test_invocable_impl([[maybe_unused]] std::integer_sequence<size_type, paramCounts...> int_seq) {
            return ((make_sequence_t<std::is_invocable, any_type, paramCounts, Func>::value) || ...);
        }
    }

    template<typename Func, size_type maxParams = 32>
    struct is_invocable {
        static constexpr bool value = internal::test_invocable_impl<Func>(std::make_index_sequence<maxParams>{});
    };

    template<typename Func, size_type maxParams = 32>
    constexpr bool is_invocable_v = is_invocable<Func, maxParams>::value;

    template<typename Func, size_type maxParams = 32>
    constexpr bool is_function_ptr_v = (std::is_empty_v<Func> || std::is_pointer_v<Func>) && is_invocable_v<Func, maxParams>;

    template<typename Func, size_type maxParams = 32>
    constexpr bool is_functor_v = requires { &Func::operator(); } && is_invocable_v<Func, maxParams>;

    template<typename Type>
    constexpr bool is_ratio_v = false; // test for ratio type

    template<int_max numerator, int_max denominator>
    constexpr bool is_ratio_v<std::ratio<numerator, denominator>> = true;

    template<typename Type>
    struct is_ratio : std::bool_constant<is_ratio_v<Type>> {};


    template<typename derived_type, typename base_type>
    using inherits_from = typename std::enable_if<std::is_base_of<base_type, derived_type>::value, int>::type;

    template<typename derived_type, typename base_type>
    using doesnt_inherit_from = typename std::enable_if<!std::is_base_of<base_type, derived_type>::value, int>::type;

    template<typename T>
    using remove_cvr = std::remove_cv<std::remove_reference_t<T>>;

    template<typename T>
    using remove_cvr_t = typename remove_cvr<T>::type;

    template <class T>
    struct is_vector
        : public std::false_type
    {
    };

    template <class T>
    struct is_vector<std::vector<T>>
        : public std::true_type
    {
    };

    template<template<typename>typename Compare, typename T, T A, T B>
    struct do_compare
    {
        static constexpr inline Compare<T> comp{};
        static constexpr inline bool value = comp(A, B);
    };

    template<template<typename>typename Compare, typename T, T A, T B>
    inline constexpr bool do_compare_v = do_compare<Compare, T, A, B>::value;

    template<rsl::size_type I, typename Type, typename... Types>
    struct element_at
#if !defined(DOXY_EXCLUDE)
        : element_at<I - 1, Types...>
    {
    };

    template<typename Type, typename... Types>
    struct element_at<0, Type, Types...>
#endif
    {
        using type = Type;
    };

    template<rsl::size_type I, typename Type, typename... Types>
    using element_at_t = typename element_at<I, Type, Types...>::type;

    template<typename T, typename... Args>
    struct is_brace_constructible
    {
    private:
        template<typename _T, typename... _Args>
        static constexpr auto check(void*)
            -> decltype(void(_T{ std::declval<_Args>()... }), std::true_type());

        template <typename...>
        static constexpr auto check(...)
            ->std::false_type;

        using type = decltype(check<T, Args...>(nullptr));
    public:
        static constexpr bool value = type::value;
    };

    template<class T, typename... Args>
    inline constexpr bool is_brace_constructible_v = is_brace_constructible<T, Args...>::value;


    template<rsl::size_type I, typename Check, typename...>
    struct element_at_is_same_as;

    template<rsl::size_type I, typename Check, typename Type, typename... Types>
    struct element_at_is_same_as<I, Check, Type, Types...> : element_at_is_same_as<I-1, Check, Type, Types...> {};

    template<typename Check, typename Type, typename... Types>
    struct element_at_is_same_as<0, Check, Type, Types...>
    {
        static constexpr bool value = ::std::is_same_v<Check, Type>;
    };

    template<rsl::size_type I, typename Check>
    struct element_at_is_same_as<I, Check>
    {
        static constexpr bool value = false;
    };

    template<rsl::size_type I, typename Check, typename... Types>
    inline constexpr bool element_at_is_same_as_v = element_at_is_same_as<I, Check, Types...>::value;

#if defined(RYTHE_MSVC)

    template<typename T>
    constexpr std::string_view type_name() noexcept {
        std::string_view funcName(__FUNCSIG__);
        auto first = funcName.find_first_of(' ', funcName.find("type_name<") + 11) + 1;
        return funcName.substr(first, funcName.find_last_of('>') - first);
    }

#elif defined(RYTHE_GCC)

    template<typename T>
    constexpr std::string_view type_name() noexcept {
        std::string_view funcName(__PRETTY_FUNCTION__);
        auto first = funcName.find_first_not_of(' ', funcName.find_first_of('=') + 1);
        return funcName.substr(first, funcName.find_last_of(';') - first);
    }

#elif defined(RYTHE_CLANG)

    template<typename T>
    constexpr std::string_view type_name() noexcept {
        std::string_view funcName(__PRETTY_FUNCTION__);
        auto first = funcName.find_first_not_of(' ', funcName.find_first_of('=') + 1);
        return funcName.substr(first, funcName.find_last_of(']') - first);
    }

#endif

    template<typename T>
    constexpr std::string_view type_name(T&&) noexcept {
        return type_name<std::remove_cvref_t<T>>();
    }



#if defined(RYTHE_MSVC) || defined(RYTHE_CLANG_MSVC)
    namespace detail
    {
        template<typename T>
        std::string getNameOfTypeImpl()
        {
            const std::string name = typeid(T).name();
            std::vector<std::string> vec = split_string_at<' '>(name);
            if (vec.size() < 2)
            {
                return name;
            }

            std::string result;
            for (auto i = 1; i < vec.size(); i++)
            {
                if (ends_with(vec[i], "struct"))
                    result += vec[i].substr(0, vec[i].size() - 6);
                else if (ends_with(vec[i], "class"))
                    result += vec[i].substr(0, vec[i].size() - 5);
                else
                    result += vec[i];
            }
            return result;
        }
    }
#elif defined(RYTHE_GCC)

#include <cxxabi.h>
    namespace detail
    {
        template<typename T>
        std::string getNameOfTypeImpl()
        {
            //Demangle the typename generated by GCC
            int status;
            char* realName = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
            std::string result = { realName };
            free(realName);
            return result;
        }
    }
#elif defined(RYTHE_CLANG_GCC)

#include <cxxabi.h>
    namespace detail
    {
        template<typename T>
        std::string getNameOfTypeImpl()
        {
            //Demangle the typename generated by GCC
            int status;
            char* realName = __cxxabiv1::__cxa_demangle(typeid(T).name(), 0, 0, &status);
            std::string result = { realName };
            free(realName);
            return result;
        }
    }
#endif

    /**@brief Returns compile-time evaluable type name.
     * @warning This version is not compiler agnostic! If you need it to be compiler agnostic use `nameOfType`.
     */
    template<typename T>
    constexpr std::string_view localNameOfType() noexcept
    {
#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
        cstring p = __PRETTY_FUNCTION__;

        while (*p++ != '=');

        for (; *p == ' '; ++p);

        cstring p2 = p;
        int count = 1;

        for (;; ++p2)
        {
            switch (*p2)
            {
            case '[':
                ++count;
                break;
            case ']':
            case ';':
                --count;
                if (!count)
                    return { p, size_type(p2 - p) };
            }
        }

        return {};
#elif defined(RYTHE_MSVC)
        cstring p = __FUNCSIG__;

        while (*p != 'T' || *(p + 1) != 'y' || *(p + 2) != 'p' || *(p + 3) != 'e' || *(p + 4) != '<')
            p++;

        while (*p++ != ' ');

        cstring p2 = p;
        int count = 1;
        size_type size = 0;

        for (; size == 0; ++p2)
        {
            switch (*p2)
            {
            case '<':
                ++count;
                break;
            case '>':
                --count;
                if (!count)
                {
                    size = (p2 - p);
                }
            }
        }

        return { p, size };

#else
#error unknown compiler
#endif
    }


    /**@brief Returns type name with namespaces other than that it's undecorated.
     * @tparam T type of which you want the name.
     */
    template<typename T>
    cstring nameOfType()
    {
        static std::string name = detail::getNameOfTypeImpl<T>();
        return name.c_str();
    }

    /**@brief Returns type name with namespaces other than that it's undecorated.
     * @tparam T type of which you want the name.
     * @param expr Variable of which you wish to auto deduct type.
     */
    template<typename T>
    cstring nameOfType(T&& expr)
    {
        return nameOfType<std::decay_t<T>>();
    }

    /**@brief Returns hash of a certain string
     * @tparam N Length of the string literal
     * @param name Name you wish to hash
     * @note Since this version takes a const char[] it can only really be used with data coming from a string literal.
     *       Because it takes in a const char[] this function is able to be constexpr and thus have minimal overhead.
     */
    template<size_type N>
    constexpr id_type nameHash(const char(&name)[N]) noexcept
    {
        id_type hash = 0xcbf29ce484222325;
        constexpr uint64 prime = 0x00000100000001b3;

        size_type size = N;
        if (name[size - 1] == '\0')
            size--;

        for (size_type i = 0; i < size; i++)
        {
            hash = hash ^ static_cast<const byte>(name[i]);
            hash *= prime;
        }

        return hash;
    }

    /**@brief Returns hash of a certain string
     * @tparam N Length of the string literal
     * @param name Name you wish to hash
     * @note Since this version takes a const char[] it can only really be used with data coming from a string literal.
     *       Because it takes in a const char[] this function is able to be constexpr and thus have minimal overhead.
     */
    template<size_type N>
    constexpr id_type nameHash(const std::array<char, N>& name) noexcept
    {
        id_type hash = 0xcbf29ce484222325;
        constexpr uint64 prime = 0x00000100000001b3;

        size_type size = N;
        if (name[size - 1] == '\0')
            size--;

        for (int i = 0; i < size; i++)
        {
            hash = hash ^ static_cast<const byte>(name[i]);
            hash *= prime;
        }

        return hash;
    }

    /**@brief Returns hash of a certain string
     * @param name Name you wish to hash
     */
    constexpr id_type nameHash(cstring name) noexcept
    {
        id_type hash = 0xcbf29ce484222325;
        constexpr uint64 prime = 0x00000100000001b3;

        for (size_type i = 0; i < rsl::constexpr_strlen(name); i++)
        {
            hash = hash ^ static_cast<const byte>(name[i]);
            hash *= prime;
        }

        return hash;
    }

    /**@brief Returns hash of a certain string
     * @param name Name you wish to hash
     */
    constexpr id_type nameHash(const std::string_view& name) noexcept
    {
        id_type hash = 0xcbf29ce484222325;
        constexpr uint64 prime = 0x00000100000001b3;

        size_type size = name.size();

        if (name[size - 1] == '\0')
            size--;

        for (size_type i = 0; i < size; i++)
        {
            hash = hash ^ static_cast<const byte>(name[i]);
            hash *= prime;
        }

        return hash;
    }
//
//    /**@brief Returns hash of a certain string
// * @param name Name you wish to hash
// */
//    id_type nameHash(const std::string& name)
//    {
//#if defined(RYTHE_MSVC) || defined(RYTHE_CLANG_MSVC)
//        static std::hash<std::string> hasher{};
//        if (!name.empty() && name[name.size() - 1] == '\0')
//            return nameHash(std::string_view(name));
//
//        return hasher(name);
//#else
//        // std::hash returns a different hash on GCC and Clang on Linux for certain CPU architectures.
//        // These certain different hashes are faster to compute but can create issues if they aren't the same.
//        return nameHash(std::string_view(name));
//#endif
//    }

    
    /**@brief Returns compile-time evaluable hash of the type name.
     * @warning This version is not compiler agnostic! If you need it to be compiler agnostic use `typeHash`.
     */
    template<typename T>
    constexpr id_type localTypeHash() noexcept
    {
        return nameHash(localNameOfType<T>());
    }

}

