# Overarching CMake script for applications.
# The Rythe root CMakeLists adds this folder as a submodule,
# this script doesn't have to do much other than add every known application in.
#add_subdirectory(test_all)

if(NOT TARGET Catch2)
    set(RYTHE_CATCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2)
    set(RYTHE_CATCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2 PARENT_SCOPE)
    if (${RYTHE_FETCH_SUBMODULES})
        message(STATUS "Downloading ${RYTHE_CATCH_DIR}")
        
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --rebase -- ${RYTHE_CATCH_DIR}
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()

    add_subdirectory(${RYTHE_CATCH_DIR})

    if(TARGET Catch2)
        set_target_properties(Catch2 PROPERTIES FOLDER "5 - tests/third_party/catch2")

        get_target_property(target_sources Catch2 SOURCES)
        foreach(src ${target_sources})
            get_filename_component(dir ${src} DIRECTORY)
            source_group("${dir}" FILES "${src}")
        endforeach()
    endif()
endif()

set(RYTHE_ENABLED_APPLICATION_NAMES ${RYTHE_ENABLED_APPLICATION_NAMES} PARENT_SCOPE)
