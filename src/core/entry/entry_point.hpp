#pragma once
#include <rsl/utilities>

#include "../program/program.hpp"

/**
 * @file entry_point.hpp
 * @brief When RYTHE_ENTRY is defined, this file will create a function with signature main(int,char**) -> int
 *        implementing the common main function of a c++ program.
 * @note When defining RYTHE_ENTRY do not create your own entry point such as main()->int, main(int,char**)->int,
 * wmain(), etc...
 * @note When using RYTHE_ENTRY you must instead implement rsl::result<void> init_program(rythe::core::program& program).
 * @note When not using RYTHE_ENTRY you must call creation and initialization of the program manually.
 */

extern rsl::result<void> init_program(rythe::core::program& program);

#if defined(RYTHE_ENTRY)

#if defined(RYTHE_WINDOWS)
__declspec(dllexport) DWORD NvOptimusEnablement = 0x0000001;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#endif

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
    rsl::current_thread::set_name("Main thread");

    rythe::core::program& program = rythe::core::this_program::get_instance();

    {
        auto result = init_program(program);
        rsl::scoped_assert_on_error saoe(false);

        if (auto errorCode = result.report_errors(); errorCode != rsl::no_error_code)
        {
            return static_cast<int>(errorCode);
        }
    }

    program.initialize();

    while (program.is_running())
    {
        program.update();
    }

    program.shutdown();
    return 0;
}
#endif
