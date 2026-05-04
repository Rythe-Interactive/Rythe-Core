#pragma once

#include <rsl/logging>
#include <rsl/memory>
#include <rsl/primitives>
#include <rsl/threading>
#include <rsl/time>
#include <rsl/type_map>

#include "engine.hpp"

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

    class program
    {
    public:
        void initialize();
        void update();
        void shutdown();

        [[nodiscard]] [[rythe_always_inline]] rsl::type_map& get_context() noexcept;
        [[nodiscard]] [[rythe_always_inline]] const rsl::type_map& get_context() const noexcept;

        [[nodiscard]] [[rythe_always_inline]] bool is_running() const;
        [[rythe_always_inline]] void stop();

        engine& add_engine_instance();

    private:
        rsl::dynamic_map<rsl::id_type, rsl::unique_object<engine>> m_engines;
        rsl::type_map m_context;
        rsl::id_type m_lastIdx = 0;
        bool m_running = false;
    };
} // namespace rythe::core

#include "program.inl"
