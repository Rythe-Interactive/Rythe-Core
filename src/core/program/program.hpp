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
	class program;

	class engine
	{
	private:
		program* m_programPtr = nullptr;
		rsl::id_type m_engineId = 0;
		rsl::pmu_allocator* m_allocator = nullptr;
		rsl::pmu_alloc_type_map m_context;

	public:
		engine(rsl::id_type id, rsl::pmu_allocator* allocator = rsl::allocator_context::threadSpecificAllocator)
			: m_engineId(id),
			  m_allocator(allocator),
			  m_context(allocator)
		{
		}

		void setup(program& program);

		void update() { rsl::log::debug("Engine[{}] Update", m_engineId); }

		void shutdown() { rsl::log::debug("Engine[{}] Shutdown", m_engineId); }

		rsl::pmu_alloc_type_map& get_context() noexcept { return m_context; }
		const rsl::pmu_alloc_type_map& get_context() const noexcept { return m_context; }

        rsl::pmu_allocator& get_allocator() noexcept { return *m_allocator; }
        const rsl::pmu_allocator& get_allocator() const noexcept { return *m_allocator; }
	};

	class program
	{
	private:
		std::unordered_map<rsl::id_type, std::unique_ptr<engine>> m_engines;
		rsl::type_map m_context;
		rsl::id_type m_lastIdx = 0;
		bool m_running = false;

	public:
		void initialize()
		{
			rsl::log::debug("Initializing Program Instance");
			for (auto& [id, engine] : m_engines)
			{
				engine->setup(*this);
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

		[[rythe_always_inline]] bool is_running() { return m_running; }

		[[rythe_always_inline]] void stop() { m_running = false; }

		[[rythe_always_inline]] engine& add_engine_instance()
		{
			return *(m_engines.emplace(m_lastIdx, std::make_unique<engine>(engine{m_lastIdx++})).first->second);
		}
	};
} // namespace rythe::core
