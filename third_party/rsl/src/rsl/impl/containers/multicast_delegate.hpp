#pragma once
#include <functional>
#include <ranges>

#include "delegate.hpp"

namespace rsl {

    template<typename ReturnType, template<typename, typename> typename ContainerType, template<typename> typename Allocator, typename... ParamTypes>
    class multicast_delegate<ReturnType(ParamTypes...), ContainerType, Allocator> final : private delegate_base<ReturnType(ParamTypes...)> {
        using base = delegate_base<ReturnType(ParamTypes...)>;
    public:
        using return_type = ReturnType;
        using param_types = type_sequence<ParamTypes...>;
        using delegate_type = delegate<ReturnType(ParamTypes...)>;

        using value_type = typename base::invocation_element;
        using allocator_type = Allocator<value_type>;
        using invocation_container = ContainerType<value_type, allocator_type>;
        using size_type = rsl::size_type;
        using difference_type = rsl::diff_type;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = typename std::allocator_traits<allocator_type>::pointer;
        using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

        using iterator = typename invocation_container::iterator;
        using const_iterator = typename invocation_container::const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
        using stub_type = typename base::stub_type;

        invocation_container m_invocationList;

        constexpr multicast_delegate(invocation_container&& e) : m_invocationList(1, e) {}

        constexpr multicast_delegate& push_back(const value_type& e) {
            std::back_inserter(m_invocationList) = e;
            return *this;
        }

        constexpr multicast_delegate& remove(const value_type& e) {
            m_invocationList.erase(std::remove(begin(), end(), e), end());
            return *this;
        }

        template<typename T>
        struct invocation_result{
            using type = std::vector<T, Allocator<T>>;
        };

        template<>
        struct invocation_result<void> {
            using type = void;
        };

        template<typename T>
        using invocation_result_t = typename invocation_result<T>::type;

    public:
        constexpr multicast_delegate() = default;
        constexpr multicast_delegate(const delegate_type& val) : m_invocationList(1, val.m_invocation) {}

        constexpr bool empty() const { return std::ranges::empty(m_invocationList); }
        constexpr void clear() { m_invocationList.clear(); }
        constexpr size_type size() const { return std::ranges::size(m_invocationList); }
        constexpr void reserve([[maybe_unused]]size_type newCap) { if constexpr (requires(invocation_container c, size_type i) { c.reserve(i); }) { m_invocationList.reserve(newCap); } }
        constexpr size_type capacity() const { if constexpr (requires(invocation_container c) { c.capacity(); }) { return m_invocationList.capacity(); } }

        constexpr auto begin() { return std::begin(m_invocationList); }
        constexpr auto cbegin() const { return std::cbegin(m_invocationList); }
        constexpr auto begin() const { return cbegin(); }
        constexpr auto rbegin() { return std::rbegin(m_invocationList); }
        constexpr auto crbegin() const { return std::crbegin(m_invocationList); }
        constexpr auto rbegin() const { return crbegin(); }

        constexpr auto end() { return std::end(m_invocationList); }
        constexpr auto cend() const { return std::cend(m_invocationList); }
        constexpr auto end() const { return cend(); }
        constexpr auto rend() { return std::rend(m_invocationList); }
        constexpr auto crend() const { return std::crend(m_invocationList); }
        constexpr auto rend() const { return crend(); }

        constexpr delegate_type& at(size_type i) { return *std::advance(begin(), i); }
        constexpr const delegate_type& at(size_type i) const { return *std::advance(cbegin(), i); }
        constexpr delegate_type& operator[](size_type i) { return at(i); }
        constexpr const delegate_type& operator[](size_type i) const { return at(i); }

        constexpr delegate_type& front() { return *begin(); }
        constexpr const delegate_type& front() const { return *cbegin(); }
        constexpr delegate_type& back() { return *std::advance(begin(), size() - 1); }
        constexpr const delegate_type& back() const { *std::advance(cbegin(), size() - 1); }

        constexpr bool operator ==(std::nullptr_t) const { return empty(); }
        constexpr bool operator !=(std::nullptr_t) const { return !empty(); }

        constexpr bool operator ==(const multicast_delegate&) const = default;
        constexpr bool operator !=(const multicast_delegate&) const = default;

        constexpr bool operator ==(const delegate_type& other) const { return size() == 1 && at(0) == other; }
        constexpr bool operator !=(const delegate_type& other) const { return !(*this == other); }

        constexpr multicast_delegate& push_back(const delegate_type& del) { return push_back(del.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& push_back(T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& push_back(const T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template <ReturnType(*TMethod)(ParamTypes...)>
        constexpr multicast_delegate& push_back() { return push_back(base::template createElement<TMethod>()); }

        template <functor Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& push_back(const Functor& instance) { return push_back(base::template createElement<Functor>(instance)); }

        constexpr multicast_delegate& operator +=(const delegate_type& another) { return push_back(another.m_invocation); }

        constexpr multicast_delegate& operator +=(delegate_type&& another) { return push_back(another.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& operator +=(T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& operator +=(const T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template <invocable Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& operator +=(const Functor& instance) { return push_back(base::template createElement<Functor>(instance)); }

        constexpr iterator erase(const_iterator pos) { return m_invocationList.erase(pos); }

        constexpr iterator erase(const_iterator first, const_iterator last) { return m_invocationList.erase(first, last); }

        constexpr void pop_back() { erase(std::advance(begin(), size() - 1)); }

        constexpr multicast_delegate& remove(const delegate_type& del) { return remove(del.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& remove(T& instance) { return remove(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& remove(const T& instance) { return remove(base::template createElement<T, TMethod>(instance)); }

        template <ReturnType(*TMethod)(ParamTypes...)>
        constexpr multicast_delegate& remove() { return remove(base::template createElement<TMethod>()); }

        template <functor Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& remove(const Functor& instance) { return remove(base::template createElement<Functor>(instance)); }

        constexpr multicast_delegate& operator -=(const delegate_type& another) { return push_back(another.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& operator -=(T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& operator -=(const T& instance) { return push_back(base::template createElement<T, TMethod>(instance)); }

        template <invocable Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& operator -=(const Functor& instance) { return remove(base::template createElement<Functor>(instance)); }

        constexpr multicast_delegate& operator =(const multicast_delegate&) = default;

        constexpr multicast_delegate& operator =(const delegate_type& del) { clear(); return push_back(del.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& operator =(T& instance) { clear(); return push_back(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& operator =(const T& instance) { clear(); return push_back(base::template createElement<T, TMethod>(instance)); }

        template <invocable Functor>
            requires std::invocable<Functor, ParamTypes...> && std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& operator =(const Functor& instance) { clear(); return push_back(base::template createElement<Functor>(instance)); }

        constexpr multicast_delegate& assign(const delegate_type& del) { return push_back(del.m_invocation); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        constexpr multicast_delegate& assign(T& instance) { clear(); return push_back(base::template createElement<T, TMethod>(instance)); }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        constexpr multicast_delegate& assign(const T& instance) { clear(); return push_back(base::template createElement<T, TMethod>(instance)); }

        template <functor Functor>
            requires std::invocable<Functor, ParamTypes...>&& std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        constexpr multicast_delegate& assign(const Functor& instance) { clear(); return push_back(base::template createElement<Functor>(instance)); }

        template<typename InputIt >
        constexpr multicast_delegate& assign(InputIt first, InputIt last) { clear(); std::copy(first, last, std::back_inserter(m_invocationList)); return *this; }

        constexpr multicast_delegate& assign(std::initializer_list<value_type> ilist) { return assign(ilist.begin(), ilist.end()); }

        constexpr auto operator()(ParamTypes... args) const { return invoke(args...); }

        constexpr auto invoke(ParamTypes... args) const -> invocation_result_t<ReturnType> {
            if constexpr (std::same_as<ReturnType, void>) {
                for (auto& m_item : m_invocationList)
                    (*m_item.m_stub)(m_item.m_object.get(), args...);
            }
            else {
                invocation_result_t<ReturnType> result;
                result.reserve(size());
                for (auto& m_item : m_invocationList)
                    result.push_back((*m_item.m_stub)(m_item.m_object.get(), args...));

                return result;
            }
        }
    };

    template<typename ReturnType, template<typename, typename> typename ContainerType = std::vector, template<typename> typename Allocator = std::allocator, typename... ParamTypes>
    multicast_delegate(const delegate<ReturnType(ParamTypes...)>&) -> multicast_delegate<ReturnType(ParamTypes...), ContainerType, Allocator>;
}

