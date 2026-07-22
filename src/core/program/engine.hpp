#pragma once

#include <rsl/logging>
#include <rsl/memory>
#include <rsl/primitives>
#include <rsl/threading>
#include <rsl/time>
#include <rsl/type_map>

namespace rythe::core
{
    class engine;
    class program;

    struct this_engine
    {
        [[nodiscard]] [[rythe_always_inline]] static rsl::type_map& get_context() noexcept;
        [[nodiscard]] [[rythe_always_inline]] static rsl::memory_allocator& get_allocator() noexcept;

        static engine& get_instance();
    };

    class engine
    {
    public:
        engine(const rsl::id_type id, rsl::allocator_storage allocator = rsl::allocator_context::threadSpecificAllocator)
            : m_engineId(id),
              m_allocator(allocator),
              m_context(allocator)
        {}

        void setup(program& program);

        void update();

        void shutdown() { rsl::log::debug("Engine[{}] Shutdown", m_engineId); }

        [[nodiscard]] rsl::type_map& get_context() noexcept { return m_context; }
        [[nodiscard]] const rsl::type_map& get_context() const noexcept { return m_context; }

        [[nodiscard]] rsl::memory_allocator& get_allocator() noexcept { return *m_allocator; }
        [[nodiscard]] const rsl::memory_allocator& get_allocator() const noexcept { return *m_allocator; }

        void bind();

    private:
        program* m_programPtr = nullptr;
        rsl::id_type m_engineId = 0;
        rsl::allocator_storage m_allocator = { nullptr };
        rsl::type_map m_context;
        rsl::time_span m_lastUpdateTime = rsl::time_span::zero;
    };
}

#include "engine.inl"
