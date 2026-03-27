#include "engine.hpp"
#include "program.hpp"


namespace rythe::core
{
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

        if (rsl::tm::main_clock.elapsed_time().seconds() > 5.f) { this_program::stop(); }
    }
}
