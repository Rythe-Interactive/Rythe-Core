project(MODULE_NAME LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(MODULE_NAME ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_configure_module(MODULE_NAME)
rythe_copy_module_output(MODULE_NAME rythe/engine/MODULE_NAME)
