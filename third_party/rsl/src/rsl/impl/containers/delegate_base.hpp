#pragma once

#include <memory>

#include "../defines.hpp"
#include "../util/concepts.hpp"
#include "../util/hash.hpp"
#include "../util/utilities.hpp"

namespace rsl {
    
    template<typename T>
    class delegate_base;
    
    template<typename ReturnType, typename... ParamTypes>
    class delegate_base<ReturnType(ParamTypes...)>	{
    protected:
        using stub_type = ReturnType(*)(void*, ParamTypes...);
        using deleter_type = void(*)(void*);
        constexpr static deleter_type defaultDeleter = []([[maybe_unused]] void*) {};

        struct invocation_element {
            using return_type = ReturnType;
            using param_types = type_sequence<ParamTypes...>;
            constexpr invocation_element() = default;
            constexpr invocation_element(void* object, stub_type stub, id_type id, deleter_type deleter = nullptr) : m_object(object, deleter ? deleter : defaultDeleter), m_ownsData(deleter != nullptr), m_stub(stub), m_id(id) {}
            constexpr invocation_element(const invocation_element& other) : m_object(other.m_object), m_ownsData(other.m_ownsData), m_stub(other.m_stub), m_id(other.m_id) {}

            constexpr bool operator ==(const invocation_element& other) const {
                return other.m_stub == m_stub && other.m_object == m_object;
            }

            constexpr bool operator !=(const invocation_element& other) const {
                return other.m_stub != m_stub || other.m_object != m_object;
            }

            std::shared_ptr<void> m_object = nullptr;
            bool m_ownsData = false;
            stub_type m_stub = nullptr;
            id_type m_id = invalid_id;
        };

        template<typename T, ReturnType(T::* method)(ParamTypes...)>
        static ReturnType method_stub(void* obj, ParamTypes... args) {
            T* p = static_cast<T*>(obj);
            return (p->*method)(std::forward<ParamTypes>(args)...);
        }

        template<typename T, ReturnType(T::* method)(ParamTypes...) const>
        static ReturnType const_method_stub(void* obj, ParamTypes... args) {
            const T* p = static_cast<const T*>(obj);
            return (p->*method)(std::forward<ParamTypes>(args)...);
        }

        template<typename T, ReturnType(T::* method)(ParamTypes...)>
        r_always_inline static id_type method_id(const T& obj) {
            return hash_combine(force_cast<size_type>(&obj), force_cast<size_type>(method));
        }

        template<typename T, ReturnType(T::* method)(ParamTypes...) const>
        r_always_inline static id_type method_id(const T& obj) {
            return hash_combine(force_cast<size_type>(&obj), force_cast<size_type>(method));
        }

        template<ReturnType(*func)(ParamTypes...)>
        static ReturnType function_stub(void* obj, ParamTypes... args) {
            return (func)(std::forward<ParamTypes>(args)...);
        }

        template<ReturnType(*func)(ParamTypes...)>
        r_always_inline static id_type function_id() {
            return force_cast<size_type>(func);
        }

        template<invocable Func>
            requires std::invocable<Func, ParamTypes...> && std::same_as<std::invoke_result_t<Func, ParamTypes...>, ReturnType> && (!functor<Func>)
        static ReturnType function_ptr_stub(void* obj, ParamTypes... args) {
            return (reinterpret_cast<Func>(obj))(std::forward<ParamTypes>(args)...);
        }

        template<invocable Func>
            requires std::invocable<Func, ParamTypes...> && std::same_as<std::invoke_result_t<Func, ParamTypes...>, ReturnType> && (!functor<Func>)
        r_always_inline static id_type function_ptr_id(Func obj) {
            return force_cast<size_type>(obj);
        }

        template<functor Functor>
            requires std::invocable<Functor, ParamTypes...> && std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        static ReturnType functor_stub(void* obj, ParamTypes... args) {
            Functor* p = static_cast<Functor*>(obj);
            return (p->operator())(std::forward<ParamTypes>(args)...);
        }

        template<functor Functor>
            requires std::invocable<Functor, ParamTypes...> && std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        r_always_inline static id_type functor_id(const Functor& obj) {
            return hash_combine(force_cast<size_type>(&obj), force_cast<size_type>(&Functor::operator()));
        }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...)>
        r_always_inline static invocation_element createElement(T& instance) {
            return invocation_element(&instance, method_stub<T, TMethod>, method_id<T, TMethod>(instance));
        }

        template<typename T, ReturnType(T::* TMethod)(ParamTypes...) const>
        r_always_inline static invocation_element createElement(const T& instance) {
            return invocation_element(const_cast<void*>(static_cast<const void*>(&instance)), const_method_stub<T, TMethod>, method_id<T, TMethod>(instance));
        }

        template <ReturnType(*TMethod)(ParamTypes...)>
        r_always_inline static invocation_element createElement() {
            return invocation_element(nullptr, function_stub<TMethod>, function_id<TMethod>());
        }

        template <invocable Functor>
            requires std::invocable<Functor, ParamTypes...> && std::same_as<std::invoke_result_t<Functor, ParamTypes...>, ReturnType>
        r_always_inline static invocation_element createElement(const Functor& instance) {
            if constexpr (!is_functor_v<Functor>) {
                return invocation_element((void*)(instance), function_ptr_stub<Functor>, function_ptr_id<Functor>(instance));
            }
            else if constexpr (std::is_empty_v<Functor>) {
                return invocation_element((void*)(&instance), functor_stub<Functor>, functor_id<Functor>(instance));
            }
            else {
                return invocation_element(new Functor(instance), functor_stub<Functor>, functor_id<Functor>(instance), [](void* vptr) {
                    Functor* ptr = static_cast<Functor*>(vptr);
                    delete ptr;
                });
            }
        }
    };

}
