#pragma once
#include <rsl/type_util>
#include <rsl/logging>
#include <rsl/delegate>
#include <rsl/hash>

#include "core/common/exception.hpp"

namespace rythe::core
{
    HAS_FUNC(onInit);
    HAS_FUNC(onShutdown);

    template<class SubSystem>
    class EngineSubSystem
    {
        template<class T>
        friend class EngineSubSystem;
    private:
        static bool m_isInitialized;
        static bool m_isShutdown;
        static bool m_constructed;

        static rsl::multicast_delegate<void()>& shutdownSequence();

        struct data
        {
            union
            {
                SubSystem inst;
                rsl::byte dummy;
            };

            data() : dummy(0) {}
            ~data() {}
        };

        static data m_data;

    protected:
        template<typename... Args>
        static SubSystem& create(Args&&... args);

        template<typename T>
        static void reportDependency();

    public:
        R_NODISCARD static SubSystem& getInstance();

        R_NODISCARD static bool initialized();

        static void init();

        static void shutdown();

        static void restart();
    };
}

#define SubSystemInstance(Type) inline static Type& instance = rythe::core::EngineSubSystem<Type>::getInstance();

#define AllowPrivateOnInit                        \
template<typename, typename>                        \
friend struct rythe::core::has_static_onInit;      \
template<typename>                                  \
friend class rythe::core::EngineSubSystem;

#define AllowPrivateOnShutdown                    \
template<typename, typename>                        \
friend struct rythe::core::has_static_onShutdown;  \
template<typename>                                  \
friend class rythe::core::EngineSubSystem;

#include <core/engine/enginesubsystem.inl>
