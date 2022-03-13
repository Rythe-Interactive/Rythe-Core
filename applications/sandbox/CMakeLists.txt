project(MODULE_NAME_sandbox LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}")
add_executable(MODULE_NAME_sandbox ${sources})
set_target_properties(MODULE_NAME_sandbox PROPERTIES FOLDER applications)

rythe_configure_engine_application(MODULE_NAME_sandbox)
