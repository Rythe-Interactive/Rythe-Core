#include "program.hpp"
#include "engine.hpp"

namespace rythe::core
{
    program& this_program::get_instance()
    {
        static program instance;
        return instance;
    }

    void program::initialize()
    {
        rsl::log::debug("Initializing Program Instance");
        for (auto& [id, engine] : m_engines) { engine->setup(*this); }
        m_running = true;
    }

    void program::update()
    {
        // In the final version the updates will be handled by a process chain
        rsl::log::debug("Program Update");
        for (auto& [id, engine] : m_engines) { engine->update(); }
    }

    void program::shutdown()
    {
        rsl::log::debug("Program Shutdown");
        for (auto& [id, engine] : m_engines) { engine->shutdown(); }
    }

    engine& program::add_engine_instance()
    {
        return *m_engines.emplace(m_lastIdx, rsl::unique_object<engine>::create_in_place(engine{ m_lastIdx++ }));
    }
} // namespace rythe::core
