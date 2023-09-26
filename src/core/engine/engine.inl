#include <core/engine/engine.hpp>
#pragma once

namespace rythe::core
{
    template<typename Func>
    inline rsl::byte Engine::subscribeToInit(Func&& func)
    {
        static_assert(sizeof(func) == sizeof(rsl::ptr_type), "Parameter passed to subscribeToInit is not a function.");
        static std::unordered_set<rsl::ptr_type> items;

        rsl::ptr_type item = rsl::force_value_cast<rsl::ptr_type>(std::forward<Func>(func));
        if (!items.count(item))
        {
            items.insert(item);
            initializationSequence() += func;
        }
        return 0;
    }

    template<typename Func>
    inline rsl::byte Engine::subscribeToShutdown(Func&& func)
    {
        static_assert(sizeof(func) == sizeof(rsl::ptr_type), "Parameter passed to subscribeToShutdown is not a function.");
        static std::unordered_set<rsl::ptr_type> items;

        rsl::ptr_type item = rsl::force_value_cast<rsl::ptr_type>(std::forward<Func>(func));
        if (!items.count(item))
        {
            items.insert(item);
            shutdownSequence() += func;
        }
        return 0;
    }

    template<typename SubSystem>
    inline rsl::byte Engine::reportSubSystem()
    {
        subscribeToInit(&SubSystem::init);
        subscribeToShutdown(&SubSystem::shutdown);
        return 0;
    }

    template <typename ModuleType, typename... Args , rsl::inherits_from<ModuleType, Module>>
    inline void Engine::reportModule(Args && ...args)
    {
        std::unique_ptr<Module> module = std::make_unique<ModuleType>(std::forward<Args>(args)...);
        m_modules[module->priority()].emplace_back(std::move(module));
    }
}
