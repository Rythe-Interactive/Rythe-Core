#define LEGION_ENTRY
#define LEGION_LOG_DEBUG

#if defined(NDEBUG)
    #define LEGION_KEEP_CONSOLE
#endif

#include <core/core.hpp>

void LEGION_CCONV reportModules(legion::Engine* engine)
{
    using namespace legion;

    log::info("Legion core sandbox");
}
