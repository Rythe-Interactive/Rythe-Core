#include "program.hpp"

namespace rythe::core
{
	void Engine::setup(Program* ptr)
	{
		rsl::log::debug("Engine[{}] Instance initialized", engineId);
		programPtr = ptr;
	}
} // namespace rythe::core
