#pragma once
#include <memory>
#include <unordered_map>

#include <rsl/type_util>
#include <rsl/delegate>
#include <rsl/primitives>

#include "core/engine/engine.hpp"
#include "core/engine/enginesubsystem.hpp"
#include "core/events/event.hpp"

/**@file eventbus.hpp
 */

namespace rythe::core::events
{
    /**@class EventBus
     * @brief Central communication channel for events and messages.
     */
    class EventBus : public EngineSubSystem<EventBus>
    {
        SubSystemInstance(EventBus);
    private:

        std::unordered_map<rsl::id_type, rsl::multicast_delegate<void(event_base&)>> m_eventCallbacks;

    public:
        /**@brief Insert event into bus and notify all subscribers.
         * @tparam event_type Event type to raise.
         * @param arguments Arguments to pass to the constructor of the event.
         */
        template<typename event_type, typename... Args CNDOXY(typename = rsl::inherits_from<event_type, event<event_type>>)>
        static void raiseEvent(Args&&... arguments);

        /**@brief Non-templated raise event function. Inserts event into bus and notifies all subscribers.
         * @param value Reference to the event to insert into the bus.
         */
        static void raiseEvent(event_base& value);

        /**@brief Unsafe, non-templated raise event function. This version is unsafe because it is allowed to trigger undefined behavior if the id is incompatible with the passed value.
         * @param value Reference to the event to insert into the bus.
         * @param id Type id of the event to invoke for. Overrides the polymorphic id of the reference passed as value.
         */
        static void raiseEventUnsafe(event_base& value, rsl::id_type id);

        /**@brief Link a callback to an event type in order to get notified whenever one gets raised.
         * @tparam event_type Event type to subscribe to.
         */
        template<typename event_type CNDOXY(typename = rsl::inherits_from<event_type, event<event_type>>)>
        static void bindToEvent(const rsl::delegate<void(event_type&)>& callback);

        /**@brief Non-templated function to link a callback to an event type in order to get notified whenever one gets raised.
         * @param id Type id of the event to subscribe to.
         * @param callback Function to bind.
         */
        static void bindToEvent(rsl::id_type id, const rsl::delegate<void(event_base&)>& callback);

        /**@brief Link a callback to an event type in order to get notified whenever one gets raised.
         * @tparam event_type Event type to subscribe to.
         */
        template<typename event_type CNDOXY(typename = rsl::inherits_from<event_type, event<event_type>>)>
        static void bindToEvent(rsl::delegate<void(event_type&)>&& callback);

        /**@brief Non-templated function to link a callback to an event type in order to get notified whenever one gets raised.
         * @param id Type id of the event to subscribe to.
         * @param callback Function to bind.
         */
        static void bindToEvent(rsl::id_type id, rsl::delegate<void(event_base&)>&& callback);

        /**@brief Link a callback to an event type in order to get notified whenever one gets raised.
         * @tparam event_type Event type to subscribe to.
         */
        template<typename event_type CNDOXY(typename = rsl::inherits_from<event_type, event<event_type>>)>
        static void unbindFromEvent(const rsl::delegate<void(event_type&)>& callback);

        /**@brief Non-templated function to link a callback to an event type in order to get notified whenever one gets raised.
         * @param id Type id of the event to subscribe to.
         * @param callback Function to bind.
         */
        static void unbindFromEvent(rsl::id_type id, const rsl::delegate<void(event_base&)>& callback);
    };

    ReportSubSystem(EventBus);
}

#include <core/events/eventbus.inl>
