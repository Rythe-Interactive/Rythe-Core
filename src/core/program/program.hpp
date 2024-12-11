#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include <rsl/logging>
#include <rsl/primitives>
#include <rsl/type_traits>
#include <rsl/type_map>

namespace rythe::core
{
	class Program;

	class Engine
	{
	private:
		Program* m_programPtr = nullptr;
		rsl::id_type m_engineId = 0;
		rsl::type_map m_context;

	public:
		Engine(rsl::id_type id)
			: m_engineId(id)
		{
		}

		void setup(Program* ptr);

		void update() { rsl::log::debug("Engine[{}] Update", m_engineId); }

		void shutdown() { rsl::log::debug("Engine[{}] Shutdown", m_engineId); }

		rsl::type_map& get_context() noexcept { return m_context; }
		const rsl::type_map& get_context() const noexcept { return m_context; }
	};

	class Program
	{
	private:
		std::unordered_map<rsl::id_type, std::unique_ptr<Engine>> m_engines;
		rsl::type_map m_context;
		rsl::id_type m_lastIdx = 0;
		bool m_running = false;

	public:
		void initialize()
		{
			rsl::log::debug("Initializing Program Instance");
			for (auto& [id, engine] : m_engines)
			{
				engine->setup(this);
			}
			m_running = true;
		}

		void update()
		{
			// In the final version the updates will be handled by a process chain
			rsl::log::debug("Program Update");
			for (auto& [id, engine] : m_engines)
			{
				engine->update();
			}
		}

		void shutdown()
		{
			rsl::log::debug("Program Shutdown");
			for (auto& [id, engine] : m_engines)
			{
				engine->shutdown();
			}
		}

		rsl::type_map& get_context() noexcept { return m_context; }
		const rsl::type_map& get_context() const noexcept { return m_context; }

		[[rythe_always_inline]] bool isRunning() { return m_running; }

		[[rythe_always_inline]] void stop() { m_running = false; }

		[[rythe_always_inline]] Engine& addEngineInstance()
		{
			return *(m_engines.emplace(m_lastIdx, std::make_unique<Engine>(Engine{m_lastIdx++})).first->second);
		}
	};
} // namespace rythe::core
