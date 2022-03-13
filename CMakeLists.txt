project(core LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(core ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_configure_module(core)
rythe_copy_module_output(core rythe/engine/core)
