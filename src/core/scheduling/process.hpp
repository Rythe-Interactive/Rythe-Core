#pragma once
#include <unordered_set>

#include <rsl/delegate>
#include <rsl/primitives>
#include <rsl/time>
#include <rsl/type_util>

#include "core/containers/hashed_sparse_set.hpp"
// #include "core/time/time.hpp"

namespace rythe::core::scheduling
{
	class Process
	{
	private:
		std::string m_name;
		rsl::id_type m_nameHash;

		std::unordered_set<rsl::id_type> m_hooks;

		rsl::delegate<void(rsl::span)> m_operation;

		rsl::span m_interval;
		rsl::span m_timebuffer;
		bool m_fixedTimeStep;

	public:
		Process() noexcept = default;

		template <rsl::size_type charc>
		Process(const char (&name)[charc], rsl::span interval = rsl::span::zero());

		Process(const std::string& name, rsl::id_type nameHash, rsl::span interval = rsl::span::zero());

		/**@brief Returns the hash of the name of the process.
		 */
		rsl::id_type id() const noexcept;

		/**@brief Returns whether the process hooks into any process-chains.
		 */
		bool inUse() const noexcept;

		/**@brief Set the operation for the process to execute at the set interval.
		 */
		void setOperation(rsl::delegate<void(rsl::span)>&& operation) noexcept;

		/**@brief Set the interval at which to execute the set operation.
		 */
		void setInterval(rsl::span interval) noexcept;

		std::unordered_set<rsl::id_type>& hooks() noexcept;

		/**@brief Update the process' internal time measurements and execute the operation if necessary.
		 * @param deltaTime Time between execute calls.
		 */
		void execute(rsl::span deltaTime);
	};
} // namespace rythe::core::scheduling

#include <core/scheduling/process.inl>
