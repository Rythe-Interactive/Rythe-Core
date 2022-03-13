project(core_sandbox LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}")
add_executable(core_sandbox ${sources})
set_target_properties(core_sandbox PROPERTIES FOLDER applications)

rythe_configure_engine_application(core_sandbox)
