#pragma once

#include <rsl/type_util>
#include <rsl/primitives>
#include <core/containers/hashed_sparse_set.hpp>
#include <core/containers/delegate.hpp>
#include <core/time/time.hpp>

namespace rythe::core::scheduling
{
    class Process
    {
    private:
        std::string m_name;
        rsl::id_type m_nameHash;

        std::unordered_set<rsl::id_type> m_hooks;

        delegate<void(time::span)> m_operation;

        time::span m_interval;
        time::span m_timebuffer;
        bool m_fixedTimeStep;

    public:
        Process() noexcept = default;

        template<rsl::size_type charc>
        Process(const char(&name)[charc], time::span interval = time::span::zero());

        Process(const std::string& name, rsl::id_type nameHash, time::span interval = time::span::zero());

        /**@brief Returns the hash of the name of the process.
         */
        rsl::id_type id() const noexcept; 

        /**@brief Returns whether the process hooks into any process-chains.
         */
        bool inUse() const noexcept; 

        /**@brief Set the operation for the process to execute at the set interval.
         */
        void setOperation(delegate<void(time::time_span<fast_time>)>&& operation) noexcept;
        
        /**@brief Set the interval at which to execute the set operation.
         */
        void setInterval(time::span interval) noexcept;

        std::unordered_set<rsl::id_type>& hooks() noexcept;

        /**@brief Update the process' internal time measurements and execute the operation if necessary.
         * @param deltaTime Time between execute calls.
         */
        void execute(time::span deltaTime);
    };
}

#include <core/scheduling/process.inl>
