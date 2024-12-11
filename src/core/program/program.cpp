#include "program.hpp"

namespace rythe::core
{
	void Engine::setup(Program* ptr)
	{
		rsl::log::debug("Engine[{}] Instance initialized", m_engineId);
		m_programPtr = ptr;
	}
} // namespace rythe::core
