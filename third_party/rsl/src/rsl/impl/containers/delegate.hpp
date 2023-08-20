#pragma once
#include <cstddef>
#include <vector>
#include <functional>
#include <algorithm>

#include "delegate_base.hpp"

namespace rsl {

    template<typename FuncSig> class delegate;
    template<typename FuncSig, template<typename, typename> typename ContainerType = std::vector, template<typename> typename Allocator = std::allocator> class multicast_delegate;

    template<typename ReturnType, typename... ParamTypes>
    class delegate<ReturnType(ParamTypes...)> final : private delegate_base<ReturnType(ParamTypes...)> {
        using base = delegate_base<ReturnType(ParamTypes...)>;
    public:
        using return_type = ReturnType;
        using param_types = type_sequence<ParamTypes...>;
        using invocation_element = typename base::invocation_element;

    private:
        using stub_type = typename base::stub_type;

        friend class multicast_delegate<ReturnType(ParamTypes...)>;
        invocation_element m_invocation;

        constexpr delegate(invocation_element&& e) : m_invocation(e) {}
    public:
        constexpr delegate() = default;

        template <ReturnType(*TMethod)(ParamTypes...)>
        constexpr delegate() : m_invocation(base::template createElement<TMethod>()) {}

        template <functor Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr delegate(const Functor& instance) : m_invocation(base::template createElement<Functor>(instance)) {}

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr static delegate create(T& instance) { return delegate(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr static delegate create(const T& instance) { return delegate(base::template createElement<T, TMethod>(instance)); }

        template <ReturnType(*TMethod)(ParamTypes...)>
        constexpr static delegate create() { return delegate(base::template createElement<TMethod>()); }

        template <functor Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr static delegate create(const Functor& instance) { return delegate(base::template createElement<Functor>(instance)); }

        constexpr bool empty() const { return m_invocation.stub == nullptr; }
        constexpr void clear() { m_invocation = invocation_element(); }

        constexpr bool operator ==(std::nullptr_t) const { return empty(); }
        constexpr bool operator !=(std::nullptr_t) const { return !empty(); }

        constexpr bool operator == (const delegate&) const = default;
        constexpr bool operator != (const delegate&) const = default;

        constexpr bool operator ==(const multicast_delegate<ReturnType(ParamTypes...)>& other) const { return other == (*this); }
        constexpr bool operator !=(const multicast_delegate<ReturnType(ParamTypes...)>& other) const { return other != (*this); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr delegate& assign(T& instance) {
            m_invocation = base::template createElement<T, TMethod>(instance);
            return *this;
        }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr delegate& assign(const T& instance) {
            m_invocation = base::template createElement<T, TMethod>(instance);
            return *this;
        }

        template <ReturnType(*TMethod)(ParamTypes...)>
        constexpr delegate& assign() {
            m_invocation = base::template createElement<TMethod>();
            return *this;
        }

        constexpr delegate& operator =(const delegate&) = default;

        template <invocable Functor>
        requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr delegate& operator =(const Functor& instance) {
            m_invocation = base::template createElement<Functor>(instance);
            return *this;
        }

        constexpr ReturnType operator()(ParamTypes... args) const {
            return invoke(args...);
        }

        constexpr ReturnType invoke(ParamTypes... args) const {
            return (*m_invocation.m_stub)(m_invocation.m_object.get(), args...);
        }
    };
}
