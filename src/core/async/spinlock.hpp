#pragma once
#include <atomic>
#include <mutex> // Anyone who includes this file can also use std::lock_guard

#include <rsl/type_util>
#include <rsl/logging>

#include "core/common/assert.hpp"

/**@file spinlock.hpp
 */

namespace rythe::core::async
{
    /**@class spinlock
     * @brief Spinlock is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
     */
    struct spinlock final
    {
    private:
        static bool m_forceRelease;
        static std::atomic_uint m_lastId;
        static thread_local std::unordered_map<rsl::id_type, rsl::uint> m_localState;
        mutable std::atomic_bool m_lock = { false };
        rsl::uint m_id = m_lastId.fetch_add(1, std::memory_order_relaxed);

    public:
        /**@brief Forces lock to no longer care about thread safety start shutting down. Should be called after all threads have been destroyed.
         */
        static void force_release(bool release = true);

        spinlock() = default;

        spinlock(spinlock&& source) noexcept;

        spinlock& operator=(spinlock&& source) noexcept;

        /**@brief Locks the spinlock, blocks if the spinlock is not available.
         */
        void lock() const noexcept;

        /**@brief Tries to lock the spinlock, returns if the spinlock is not available.
         */
        R_NODISCARD bool try_lock() const noexcept;

        /**@brief Unlocks the spinlock.
         */
        void unlock() const noexcept;
    };

    template<typename resource_type>
    using lock_pair = std::pair<spinlock, resource_type>;
}
