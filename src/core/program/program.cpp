#include "program.hpp"

namespace rythe::core
{
    rsl::type_map& this_program::get_context() noexcept
    {
        return get_instance().get_context();
    }

    bool this_program::is_running() noexcept
    {
        return get_instance().is_running();
    }

    void this_program::stop() noexcept
    {
        get_instance().stop();
    }

    program& this_program::get_instance()
    {
        static program instance;
        return instance;
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

        if (rsl::tm::main_clock.elapsed_time().seconds() > 5.f)
        {
            this_program::stop();
        }
    }
} // namespace rythe::core
