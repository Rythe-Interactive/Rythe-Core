#pragma once
#include <iostream>
#include <rsl/logging>
#include <rsl/primitives>
#include <rsl/type_util>
#include <rsl/utilities>

#include "..\program\program.hpp"

/**
 * @file entry_point.hpp
 * @brief When RYTHE_ENTRY is defined, this file will create a function with signature main(int,char**) -> int
 *        implementing the common main function of a c++ program.
 * @note When defining RYTHE_ENTRY do no create your own CRT_STARTUP such as main()->int, main(int,char**)->int,
 * wmain(), etc...
 * @note When using RYTHE_ENTRY you must instead implement reportModules(rythe::core::Engine*).
 * @note When not using RYTHE_ENTRY you must call creation and initialization of the engine manually.
 */


/**@brief Reports engine modules to the engine, must be implemented by you.
 * @param [in] engine The engine object
 * @ref rythe::core::Engine::reportModule<T,...>()
 */
extern rsl::result<void> init_program(rythe::core::Program& program);

#if defined(RYTHE_ENTRY)

	#if defined(RYTHE_WINDOWS)
__declspec(dllexport) DWORD NvOptimusEnablement = 0x0000001;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	#endif


int main(int argc, char** argv)
{
	rsl::log::setup();
	rythe::core::Program program;

	if (auto errorCode = init_program(program).report_errors(); errorCode != rsl::no_error_code)
	{
		return static_cast<int>(errorCode);
	}

	program.initialize();

	while (program.isRunning())
	{
		program.update();
	}

	program.shutdown();
	return 0;
}
#endif
