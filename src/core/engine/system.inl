#include <core/engine/system.hpp>
#pragma once
#include <core/ecs/registry.hpp>
#include <core/scheduling/scheduling.hpp>
#include <core/events/eventbus.hpp>

namespace rythe::core
{
    template<typename SelfType>
    template <void(SelfType::* func_type)(rsl::span), rsl::size_type charc>
    inline rythe_always_inline rsl::id_type System<SelfType>::createProcess(const char(&processChainName)[charc], rsl::span interval)
    {
        std::string name = std::string(processChainName) + rsl::nameOfType<SelfType>() + std::to_string(interval) + std::to_string(rsl::force_value_cast<rsl::ptr_type>(func_type));
        rsl::id_type id = rsl::nameHash(name);
        std::unique_ptr<schd::Process> process = std::make_unique<schd::Process>(name, id, interval);

        process->setOperation(std::move(rsl::delegate<void(rsl::span)>::create<SelfType, func_type>(*reinterpret_cast<SelfType*>(this))));

        m_processes.emplace(id, std::move(process));

        schd::Scheduler::hookProcess<charc>(processChainName, pointer<schd::Process>{ m_processes[id].get() });
        return id;
    }

    template<typename SelfType>
    template<typename event_type, void(SelfType::* func_type)(event_type&) CNDOXY(typename)>
    inline rythe_always_inline rsl::id_type System<SelfType>::bindToEvent()
    {
        rsl::id_type id = rsl::combine_hash(event_type::id, rsl::force_value_cast<rsl::ptr_type>(func_type));

        auto temp = rsl::delegate<void(event_type&)>::template create<SelfType, func_type>(*reinterpret_cast<SelfType*>(this));
        auto& del = m_bindings.try_emplace(id, reinterpret_cast<rsl::delegate<void(events::event_base&)>&&>(std::move(temp))).first->second;

        events::EventBus::bindToEvent<event_type>(reinterpret_cast<rsl::delegate<void(event_type&)>&>(del));

        return id;
    }

    template <typename event_type CNDOXY(typename)>
    inline rythe_always_inline void SystemBase::unbindFromEvent(rsl::id_type bindingId)
    {
        events::EventBus::unbindFromEvent<event_type>(reinterpret_cast<rsl::delegate<void(event_type&)>&>(m_bindings.at(bindingId)));
        m_bindings.erase(bindingId);
    }

    template<typename event_type, typename... Args CNDOXY(typename)>
    inline rythe_always_inline void SystemBase::raiseEvent(Args&&... arguments)
    {
        events::EventBus::raiseEvent<event_type>(std::forward<Args>(arguments)...);
    }

    template<typename SelfType>
    template<typename Func>
    inline rythe_always_inline auto System<SelfType>::queueJobs(rsl::size_type count, Func&& func)
    {
        if constexpr (std::is_invocable_v<Func, rsl::id_type>)
        {
            return schd::Scheduler::queueJobs(count, [&]() {
                std::invoke(func, async::this_job::get_id());
                });
        }
        else
        {
            static_assert(std::is_invocable_v<Func>, "Func type should be invocable with either an id as a parameter or with no parameters.");
            return schd::Scheduler::queueJobs(count, std::forward<Func>(func));
        }
    }

    template<typename SelfType>
    template<void(SelfType::* func_type)()>
    inline rythe_always_inline auto System<SelfType>::queueJobs(rsl::size_type count)
    {
        return schd::Scheduler::queueJobs(count, [&]() {
            std::invoke(func_type, this, async::this_job::get_id());
            });
    }

    template<typename SelfType>
    template<void(SelfType::* func_type)(rsl::id_type)>
    inline rythe_always_inline auto System<SelfType>::queueJobs(rsl::size_type count)
    {
        return schd::Scheduler::queueJobs(count, [&]() {
            std::invoke(func_type, this);
            });
    }

}
