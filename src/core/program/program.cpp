#include "program.hpp"

namespace rythe::core
{
	void engine::setup(program& program)
	{
		rsl::log::debug("Engine[{}] Instance initialized", m_engineId);
		m_programPtr = &program;
	}
} // namespace rythe::core
