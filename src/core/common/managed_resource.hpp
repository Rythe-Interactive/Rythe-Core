#pragma once
#include <unordered_map>
#include <memory>
#include <type_traits>

#include <rsl/delegate>

#include "core/common/assert.hpp"
#include "core/async/rw_spinlock.hpp"

namespace rythe::core::common
{
    template<typename R, typename C, typename... Args>
    C functor_class(R(C::*)(Args...)) { return std::declval<C>(); }

    namespace detail
    {
        template<typename T>
        struct _managed_resource_del
        {
        private:
            T* m_store;

        public:
            _managed_resource_del(_managed_resource_del&&) noexcept = default;

            constexpr _managed_resource_del(T* src) noexcept : m_store(src) {}

            void operator()(rsl::delegate<void(T&)>* const _ptr) const
            {
                _ptr->invoke(*m_store);
                delete _ptr;
            }
        };
    }

    template<typename T>
    struct managed_resource
    {
    public:
        T value;

    private:
        std::shared_ptr<rsl::delegate<void(T&)>> m_ref_counter;

    public:
        explicit managed_resource(std::nullptr_t) : value(), m_ref_counter(nullptr) {}

        template<typename... Args>
        managed_resource(void(*destroyFunc)(T&), Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
            : value(std::forward<Args>(args)...)
        {
            rsl::delegate<void(T&)> del;
            del = destroyFunc;
            m_ref_counter = std::make_shared<rsl::delegate<void(T&)>>(del, detail::_managed_resource_del<T>{ &value });
        }

        template<typename... Args>
        managed_resource(rsl::delegate<void(T&)> destroyFunc, Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
            : value(std::forward<Args>(args)...),
            m_ref_counter(new rsl::delegate<void(T&)>(destroyFunc), detail::_managed_resource_del<T>{ &value })
        {
        }

        managed_resource(const managed_resource<T>& src) noexcept(std::is_nothrow_copy_constructible_v<T>)
            : value(src.value), m_ref_counter(src.m_ref_counter)
        {
        }

        managed_resource(managed_resource<T>&& src) noexcept(std::is_nothrow_move_constructible_v<T>)
            : value(std::move(src.value)), m_ref_counter(std::move(src.m_ref_counter))
        {
        }

        managed_resource<T>& operator=(const managed_resource<T>& src) noexcept(std::is_nothrow_copy_assignable_v<T>)
        {
            value = src.value;
            m_ref_counter = src.m_ref_counter;
            return *this;
        }

        managed_resource<T>& operator=(managed_resource<T>&& src) noexcept(std::is_nothrow_move_assignable_v<T>)
        {
            value = std::move(src.value);
            m_ref_counter = std::move(src.m_ref_counter);
            return *this;
        }

        T* operator&()
        {
            return &value;
        }

        operator T& ()
        {
            return value;
        }

        operator const T& () const
        {
            return value;
        }
    };
}
