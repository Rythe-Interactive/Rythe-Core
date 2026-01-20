#pragma once

#include <rsl/logging>
#include <rsl/memory>
#include <rsl/primitives>
#include <rsl/threading>
#include <rsl/time>
#include <rsl/type_map>

namespace rythe::core
{
    class program;

    struct this_program
    {
        [[nodiscard]] [[rythe_always_inline]] static rsl::type_map& get_context() noexcept;

        [[nodiscard]] [[rythe_always_inline]] static bool is_running() noexcept;

        [[rythe_always_inline]] static void stop() noexcept;

        static program& get_instance();
    };

    class engine
    {
    public:
        engine(const rsl::id_type id, rsl::pmu_allocator* allocator = rsl::allocator_context::threadSpecificAllocator)
            : m_engineId(id),
              m_allocator(allocator),
              m_context(allocator)
		{
		}

        void setup(program& program);

		void update();

        void shutdown() { rsl::log::debug("Engine[{}] Shutdown", m_engineId); }

        [[nodiscard]] rsl::pmu_alloc_type_map& get_context() noexcept { return m_context; }
        [[nodiscard]] const rsl::pmu_alloc_type_map& get_context() const noexcept { return m_context; }

        [[nodiscard]] rsl::pmu_allocator& get_allocator() noexcept { return *m_allocator; }
        [[nodiscard]] const rsl::pmu_allocator& get_allocator() const noexcept { return *m_allocator; }

    private:
        program* m_programPtr = nullptr;
        rsl::id_type m_engineId = 0;
        rsl::pmu_allocator* m_allocator = nullptr;
        rsl::pmu_alloc_type_map m_context;
    };

    class program
    {
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

        [[nodiscard]] rsl::type_map& get_context() noexcept { return m_context; }
        [[nodiscard]] const rsl::type_map& get_context() const noexcept { return m_context; }

        [[nodiscard]] [[rythe_always_inline]] bool is_running() const { return m_running; }

        [[rythe_always_inline]] void stop() { m_running = false; }

        [[rythe_always_inline]] engine& add_engine_instance()
        {
            return *m_engines.emplace(m_lastIdx, rsl::unique_object<engine>::create_in_place(engine{m_lastIdx++}));
        }

    private:
        rsl::dynamic_map<rsl::id_type, rsl::unique_object<engine>> m_engines;
        rsl::type_map m_context;
        rsl::id_type m_lastIdx = 0;
        bool m_running = false;
    };
} // namespace rythe::core
