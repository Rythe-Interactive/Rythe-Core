#include <core/scheduling/scheduler.hpp>
#pragma once

namespace rythe::core::scheduling
{
	template <typename Function, typename... Args>
	inline pointer<std::thread> scheduling::Scheduler::createThread(Function&& function, Args&&... args)
	{
		if (instance.m_availableThreads) // Check if there are available threads.
		{
			instance.m_availableThreads--;

			std::thread newThread{std::forward<Function>(function), std::forward<Args>(args)...}; // Create a new thread and run it.
			std::thread::id id = newThread.get_id();

			auto [it, _] = instance.m_threads.emplace(id, std::move(newThread));
			return {&it->second};
		}

		return {nullptr};
	}

	template <typename functor, typename... argument_types>
	inline rythe_always_inline pointer<std::thread> Scheduler::reserveThread(functor&& function, argument_types&&... args)
	{
		return createThread(std::forward<functor>(function), std::forward<argument_types>(args)...);
	}

	template <typename Func>
	inline auto Scheduler::queueJobs(rsl::size_type count, Func&& func)
	{
		auto repeater = [](rsl::size_type l_count, auto l_func)
		{ return queueJobs(l_count, l_func); };

		if (!count)
			return async::job_operation(std::shared_ptr<async::async_progress<void>>(nullptr), std::shared_ptr<async::job_pool>(nullptr), repeater, tryCompleteJobPool);

		std::shared_ptr<async::job_pool> jobPool = std::make_shared<async::job_pool>(count, func);

		auto& [lock, jobQueue] = instance.m_jobs;
		{
			async::readwrite_guard guard(lock);
			jobQueue.push_back(jobPool);
		}
		return async::job_operation(jobPool->get_progress(), jobPool, repeater, tryCompleteJobPool);
	}

	template <rsl::size_type charc>
	inline pointer<ProcessChain> Scheduler::createProcessChain(const char (&name)[charc])
	{
		rsl::id_type id = rsl::nameHash<charc>(name);
		return {&instance.m_processChains.emplace(id, name, id).first.value()};
	}

	template <rsl::size_type charc>
	inline pointer<ProcessChain> Scheduler::getChain(const char (&name)[charc])
	{
		rsl::id_type id = rsl::nameHash<charc>(name);
		if (instance.m_processChains.contains(id))
			return {&instance.m_processChains.at(id)};
		return {nullptr};
	}

	template <rsl::size_type charc>
	inline bool Scheduler::hookProcess(const char (&processChainName)[charc], Process& process)
	{
		rsl::id_type chainId = rsl::nameHash<charc>(processChainName);

		if (instance.m_processChains.contains(chainId))
		{
			instance.m_processChains[chainId].addProcess(process);
			return true;
		}

		return false;
	}

	template <rsl::size_type charc>
	inline bool Scheduler::hookProcess(const char (&processChainName)[charc], pointer<Process> process)
	{
		rsl::id_type chainId = rsl::nameHash<charc>(processChainName);

		if (instance.m_processChains.contains(chainId))
		{
			instance.m_processChains[chainId].addProcess(process);
			return true;
		}

		return false;
	}

	template <rsl::size_type charc>
	inline bool Scheduler::unhookProcess(const char (&chainName)[charc], Process& process)
	{
		rsl::id_type chainId = rsl::nameHash<charc>(chainName);

		if (instance.m_processChains.contains(chainId))
			return instance.m_processChains[chainId].removeProcess(process);

		return false;
	}

	template <rsl::size_type charc>
	inline bool Scheduler::unhookProcess(const char (&chainName)[charc], pointer<Process> process)
	{
		rsl::id_type chainId = rsl::nameHash<charc>(chainName);

		if (instance.m_processChains.contains(chainId))
			return instance.m_processChains[chainId].removeProcess(process);

		return false;
	}

} // namespace rythe::core::scheduling
