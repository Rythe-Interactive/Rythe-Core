#pragma once

#define EXPAND(x) x

#define _CONCAT_IMPL_(A, B) A ## B

#define CONCAT(A, B) _CONCAT_IMPL_(A, B)

#define ANONYMOUS_NAME(x) CONCAT(x, __LINE__)

#define ANON_VAR(Type, Category) inline static Type EXPAND(ANONYMOUS_NAME(Category))

#define STRINGIFY(x) #x

#if defined(DOXY_EXCLUDE)
#   define NDOXY(...)
#   define CNDOXY(...)
#else
#   define NDOXY(args...) args
#   define CNDOXY(args...) , args
#endif


#define RYTHE_DEBUG_VALUE 1
#define RYTHE_RELEASE_VALUE 2

#if defined(_DEBUG) || defined(DEBUG)
/**@def RYTHE_DEBUG
 * @brief Defined in debug mode.
 */
#   define RYTHE_DEBUG
#   define RYTHE_CONFIGURATION RYTHE_DEBUG_VALUE

#   if !defined(RYTHE_VALIDATE)
#       define RYTHE_VALIDATE
#   endif
#else
/**@def RYTHE_RELEASE
 * @brief Defined in release mode.
 */
#   define RYTHE_RELEASE 
#   define RYTHE_CONFIGURATION RYTHE_RELEASE_VALUE
#endif

#if !defined(RYTHE_VALIDATION_LEVEL)
#   if defined(RYTHE_VALIDATE)
#       define RYTHE_VALIDATION_LEVEL 1
#   else
#       define RYTHE_VALIDATION_LEVEL 0
#   endif
#endif

#pragma region /////////////////////////////////// Operating system /////////////////////////////////////

#if defined(_WIN64)
#   define RYTHE_WINDOWS
#elif defined(__linux__)
#   define RYTHE_LINUX
#endif

#pragma endregion

#pragma region //////////////////////////////////// Detect compiler /////////////////////////////////////

#if defined(__clang__)
 // clang
#   define RYTHE_CLANG
#   if defined(__GNUG__) || (defined(__GNUC__) && defined(__cplusplus))
#       define RYTHE_CLANG_GCC
#   elif defined(_MSC_VER)
#       define RYTHE_CLANG_MSVC
#   endif
#elif defined(__GNUG__) || (defined(__GNUC__) && defined(__cplusplus))
 // gcc
#   define RYTHE_GCC
#elif defined(_MSC_VER)
 // msvc
#   define RYTHE_MSVC
#endif

#pragma endregion

#pragma region ////////////////////////////////// Compiler specifics ////////////////////////////////////

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define nullop() asm volatile("nop");
#elif defined(RYTHE_MSVC)
#   include <intrin.h>
#   define nullop() __nop();
#else
#   define nullop() ;
#endif

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define pause_instruction __builtin_ia32_pause
#elif defined(RYTHE_MSVC)
#   define pause_instruction _mm_pause
#else
#   define pause_instruction nullop
#endif

#if !defined(__FULL_FUNC__)
#   if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#       define __FULL_FUNC__ __PRETTY_FUNCTION__
#   elif defined(RYTHE_MSVC)
#       define __FULL_FUNC__ __FUNCSIG__
#   else
#       define __FULL_FUNC__ __func__
#   endif
#endif

#if defined(RYTHE_CLANG)
#   define RYTHE_PRAGMA_TO_STR(x) _Pragma(#x)
#   define RYTHE_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#   define RYTHE_CLANG_SUPPRESS_WARNING(w) RYTHE_PRAGMA_TO_STR(clang diagnostic ignored w)
#   define RYTHE_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#   define RYTHE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_CLANG_SUPPRESS_WARNING_PUSH RYTHE_CLANG_SUPPRESS_WARNING(w)
#else
#   define RYTHE_CLANG_SUPPRESS_WARNING_PUSH
#   define RYTHE_CLANG_SUPPRESS_WARNING(w)
#   define RYTHE_CLANG_SUPPRESS_WARNING_POP
#   define RYTHE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined(RYTHE_GCC)
#   define RYTHE_PRAGMA_TO_STR(x) _Pragma(#x)
#   define RYTHE_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#   define RYTHE_GCC_SUPPRESS_WARNING(w) RYTHE_PRAGMA_TO_STR(GCC diagnostic ignored w)
#   define RYTHE_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#   define RYTHE_GCC_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_GCC_SUPPRESS_WARNING_PUSH RYTHE_GCC_SUPPRESS_WARNING(w)
#else
#   define RYTHE_GCC_SUPPRESS_WARNING_PUSH
#   define RYTHE_GCC_SUPPRESS_WARNING(w)
#   define RYTHE_GCC_SUPPRESS_WARNING_POP
#   define RYTHE_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined(RYTHE_MSVC)
#   define RYTHE_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#   define RYTHE_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#   define RYTHE_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#   define RYTHE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_MSVC_SUPPRESS_WARNING_PUSH RYTHE_MSVC_SUPPRESS_WARNING(w)
#else
#   define RYTHE_MSVC_SUPPRESS_WARNING_PUSH
#   define RYTHE_MSVC_SUPPRESS_WARNING(w)
#   define RYTHE_MSVC_SUPPRESS_WARNING_POP
#   define RYTHE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined (RYTHE_MSVC)
#   define COMPILER_WARNING(desc) __pragma(message(__FILE__ "(" STRINGIFY(__LINE__) ") : warning: " #desc))
#   define COMPILER_ERROR(desc) __pragma(message(__FILE__ "(" STRINGIFY(__LINE__) ") : error: " #desc))
#elif defined(RYTHE_GCC) || defined(RYTHE_CLANG)
#   define COMPILER_WARNING(desc) _Pragma(STRINGIFY(GCC warning desc))
#   define COMPILER_ERROR(desc) _Pragma(STRINGIFY(GCC error desc))
#endif

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define R_NULLOP() asm volatile("nop");
#elif defined(RYTHE_MSVC)
#   include <intrin.h>
#   define R_NULLOP() __nop();
#else
#   define R_NULLOP() ;
#endif

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define R_PAUSE_INSTRUCTION __builtin_ia32_pause
#elif defined(RYTHE_MSVC)
#   define R_PAUSE_INSTRUCTION _mm_pause
#else
#   define R_PAUSE_INSTRUCTION L_NULLOP
#endif

#if !defined(__FULL_FUNC__)
#   if defined(RYTHE_CLANG) || defined(RYTHE__GCC)
#       define __FULL_FUNC__ __PRETTY_FUNCTION__
#   elif defined(RYTHE_MSVC)
#       define __FULL_FUNC__ __FUNCSIG__
#   else
#       define __FULL_FUNC__ __func__
#   endif
#endif

/**@def RYTHE_PURE
 * @brief Marks a function as pure virtual.
 */
#define RYTHE_PURE =0

/**@def RYTHE_IMPURE
 * @brief Marks a function as overridable but default implemented.
 */
#define RYTHE_IMPURE {}

/**@def RYTHE_IMPURE_RETURN
 * @brief Marks a function as overridable but default implemented with certain default return value.
 * @param x value the function should return.
 */
#define RYTHE_IMPURE_RETURN(x) { return (x); }


#define RULE_OF_5(type)\
type() = default;\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;\
~type() = default;

#define RULE_OF_5_NOEXCEPT(type)\
type() noexcept = default;\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;\
~type() = default;

#define NO_DEF_CTOR_RULE5(type)\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;\
~type() = default;

#define NO_DEF_CTOR_RULE5_NOEXCEPT(type)\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;\
~type() = default;

#define NO_DTOR_RULE5(type)\
type() = default;\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;

#define NO_DTOR_RULE5_NOEXCEPT(type)\
type() noexcept = default;\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;

#define COPY_FUNCS(type)\
type(const type&) = default;\
type& operator=(const type&) = default;

#define COPY_FUNCS_DECO(pre, type, post)\
pre type(const type&) post = default;\
pre type& operator=(const type&) post = default;

#define COPY_FUNCS_NOEXCEPT(type)\
type(const type&) noexcept = default;\
type& operator=(const type&) noexcept = default;

#define MOVE_FUNCS(type)\
type(type&&) = default;\
type& operator=(type&&) = default;

#define MOVE_FUNCS_DECO(pre, type, post)\
pre type(type&&) post = default;\
pre type& operator=(type&&) post = default;

#define MOVE_FUNCS_NOEXCEPT(type)\
type(type&&) noexcept = default;\
type& operator=(type&&) noexcept = default;

#pragma endregion


#if (defined(RYTHE_WINDOWS) && !defined(RYTHE_WINDOWS_USE_CDECL)) || defined(DOXY_INCLUDE)
    /**@def RYTHE_CCONV
     * @brief the calling convention exported functions will use in the args engine
     */
#   define RYTHE_CCONV __fastcall
#elif defined(RYTHE_MSVC)
#   define RYTHE_CCONV __cdecl
#else
#   define RYTHE_CCONV
#endif

#pragma region ////////////////////////////////// Language convention ///////////////////////////////////

/**@def RYTHE_CPP17V
 * @brief the version number of c++17 as long
 */
#define RYTHE_CPP17V 201703L

/**@def NO_MANGLING
 * @brief exports functions with C style names instead of C++ mangled names
 */
#define NO_MANGLING extern "C"

/**@def RYTHE_FUNC
 * @brief export setting + calling convention used by the engine
 */
#define RYTHE_FUNC RYTHE_CCONV

/**@def RYTHE_INTERFACE
 * @brief un-mangled function name +  export setting + calling convention used by the engine
 */
#define RYTHE_INTERFACE NO_MANGLING RYTHE_CCONV 

#if !defined(__FUNC__)
#   define __FUNC__ __func__ 
#endif

#pragma endregion

#pragma region ///////////////////////////////////// Attributes /////////////////////////////////////////

#if defined(RYTHE_GCC) || defined(RYTHE_CLANG)
#   define r_always_inline __attribute__((always_inline))
#elif defined(RYTHE_MSVC)
#   define r_always_inline __forceinline
#else
#   define r_always_inline inline
#endif

#define R_ALWAYS_INLINE r_always_inline

#if defined(__has_cpp_attribute) || defined(DOXY_INCLUDE) 
    /**@def R_HASCPPATTRIB
     * @brief checks if a certain attribute exists in this version of c++
     * @param x attribute you want to test for
     * @return true if attribute exists
     */
#   define R_HASCPPATTRIB(x) __has_cpp_attribute(x)
#else
#   define R_HASCPPATTRIB(x) 0
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(fallthrough) || defined(DOXY_INCLUDE)
#   define R_FALLTHROUGH [[fallthrough]]
#else
#   define R_FALLTHROUGH
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(maybe_unused) || defined(DOXY_INCLUDE)
    /**@def R_MAYBEUNUSED
     * @brief [[maybe_unused]]
     */
#   define R_MAYBEUNUSED [[maybe_unused]]
#else
#   define R_MAYBEUNUSED
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(nodiscard) || defined(DOXY_INCLUDE)
    /**@def R_NODISCARD
     * @brief Marks a function as "nodiscard" meaning that result must be captured and should not be discarded.
     */
#   define R_NODISCARD [[nodiscard]]
#else
#   define R_NODISCARD
#endif

#if __cplusplus > RYTHE_CPP17V || R_HASCPPATTRIB(noreturn) || defined(DOXY_INCLUDE)
    /**@def L_NORETURN
     * @brief Marks a function as "noreturn" meaning that the function will never finish, or terminate the application
     */
#   define R_NORETURN [[noreturn]]
#else
#   define R_NORETURN
#endif

#pragma endregion

#if !defined(DOXY_EXCLUDE)
#define HAS_FUNC(x)                                                                                                     \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_, x) {                                                                                            \
        static_assert(std::integral_constant<T, false>::value, "Second template param needs to be of function type.");  \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename Ret, typename... Args>                                                                \
    struct CONCAT(has_, x)<C, Ret(Args...)> {                                                                           \
    private:                                                                                                            \
        template<typename T>                                                                                            \
        static constexpr auto check(T*)                                                                                 \
            -> typename std::is_same<decltype(std::declval<T>(). x (std::declval<Args>()...)), Ret>::type;              \
                                                                                                                        \
        template <typename>                                                                                             \
        static constexpr auto check(...)                                                                                \
            ->std::false_type;                                                                                          \
                                                                                                                        \
        typedef decltype(check<C>(nullptr)) type;                                                                       \
    public:                                                                                                             \
        static constexpr bool value = type::value;                                                                      \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_, CONCAT(x, _v)) = CONCAT(has_, x)<C, F>::value;                                          \
                                                                                                                        \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_static_, x) {                                                                                     \
        static_assert(std::integral_constant<T, false>::value, "Second template param needs to be of function type.");  \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename Ret, typename... Args>                                                                \
    struct CONCAT(has_static_, x)<C, Ret(Args...)> {                                                                    \
    private:                                                                                                            \
        template<typename T>                                                                                            \
        static constexpr auto check(T*)                                                                                 \
            -> typename std::is_same<decltype(T:: x (std::declval<Args>()...)), Ret>::type;                             \
                                                                                                                        \
        template <typename>                                                                                             \
        static constexpr auto check(...)                                                                                \
            ->std::false_type;                                                                                          \
                                                                                                                        \
        typedef decltype(check<C>(nullptr)) type;                                                                       \
    public:                                                                                                             \
        static constexpr bool value = type::value;                                                                      \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_static_, CONCAT(x, _v)) = CONCAT(has_static_, x)<C, F>::value;
#else
#define HAS_FUNC(x)                                                                                                     \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_, x) {                                                                                            \
        static constexpr bool value = false;                                                                            \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_, CONCAT(x, _v)) = CONCAT(has_, x)<C, F>::value;                                          \
                                                                                                                        \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_static_, x) {                                                                                     \
        static constexpr bool value = false;                                                                            \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_static_, CONCAT(x, _v)) = CONCAT(has_static_, x)<C, F>::value;
#endif

HAS_FUNC(setup);
HAS_FUNC(shutdown);
HAS_FUNC(update);

HAS_FUNC(begin);
HAS_FUNC(end);
HAS_FUNC(at);

HAS_FUNC(size);
HAS_FUNC(resize);

HAS_FUNC(push_back);
HAS_FUNC(emplace);
HAS_FUNC(insert);
