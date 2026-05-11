#include "engine.hpp"
#include "program.hpp"


namespace rythe::core
{
    namespace
    {
        thread_local rsl::id_type currentEngineId;
    }

    engine& this_engine::get_instance()
    {
        return this_program::get_engine_instance(currentEngineId);
    }

    void engine::setup(program& program)
    {
        rsl::log::debug("Engine[{}] Instance initialized", m_engineId);
        m_programPtr = &program;
    }

    void engine::update()
    {
        using namespace rsl::literals;

        rsl::log::debug("Engine[{}] Update", m_engineId);

        rsl::current_thread::sleep_for(1_s);

        if (rsl::main_clock.elapsed_time().seconds() > 5.f) { this_program::stop(); }
    }

    void engine::bind()
    {
        currentEngineId = m_engineId;
    }
}
