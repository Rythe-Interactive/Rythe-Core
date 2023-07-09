#pragma once
#include <memory>
#include <type_traits>

#include <rsl/primitives>
#include <core/types/meta.hpp>
#include <core/types/type_util.hpp>
#include <rsl/type_util>
#include <core/containers/delegate.hpp>
#include <core/engine/system.hpp>

/**
 * @file module.hpp
 */

namespace rythe::core
{
    /**@class Module
     * @brief interface for engine-modules, must be implemented
     * @ref rythe::core::Engine::reportModule<T,...>()
     */
    class Module
    {
        friend class Engine;
    private:
        multicast_delegate<void()> m_setupFuncs;
        multicast_delegate<void()> m_shutdownFuncs;

        std::unordered_map<rsl::id_type, std::unique_ptr<SystemBase>> m_systems;

        void init()
        {
            m_setupFuncs.invoke();
        }

        void shutdown()
        {
            m_shutdownFuncs.invoke();
        }

    protected:
        template<rsl::size_type charc>
        void createProcessChain(const char(&name)[charc]) const;

        template<typename SystemType, typename... Args>
        void reportSystem(Args&&... args);

        template<typename component_type, typename... Args>
        void registerComponentType(Args&&... args);

    public:
        virtual void setup() RYTHE_PURE;

        /**@brief determines the execution priority of this module
         * @ref RYTHE_IMPURE_RETURN
         * @returns priority_type signed int8 higher is higher priority and get called first
         * @note default priority of the engine is 0.
         * @note call order for modules with the same priority is undefined.
         */
        virtual priority_type priority() RYTHE_IMPURE_RETURN(default_priority);

        virtual ~Module() = default;
    };
}
