#pragma once
#include <unordered_map>

#include <rsl/primitives>
#include <rsl/type_util>

#include "core/async/ring_sync_lock.hpp"

/**
 * @file event.hpp
 */

namespace rythe::core::events
{
    /**@class event_base
     * @brief Base class of all events for polymorphic storage.
     */
    struct event_base
    {
        virtual ~event_base() = default;

        /**@brief Get's the type id of an event. (only available in event_base)
         */
        virtual rsl::id_type get_id() RYTHE_PURE;
    };

    /**@class event
     * @brief Base class all user defined events should inherit from. This ensures that each event has it's type id and that it can statically be requested.
     */
    template<typename Self>
    struct event : public event_base
    {
        friend  class EventBus;

        inline static const rsl::id_type id = typeHash<Self>();

        virtual ~event() = default;
    private:
        virtual rsl::id_type get_id()
        {
            return id;
        }
    };
}
