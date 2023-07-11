#include <core/events/defaultevents.hpp>
#include <core/scheduling/scheduler.hpp>
#include <rsl/logging>

namespace rythe::core::events
{
    exit::exit(int exitCode) : exitcode(exitCode)
    {
    }
}
