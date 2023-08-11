#include "error_handling.hpp"

namespace rsl {
    thread_local errc error_context::errorCode = success;
    thread_local buffered_string<RSL_ERR_MESSAGE_MAX_LENGTH> error_context::errorMessage;
}
