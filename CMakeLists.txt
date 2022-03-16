project(core LANGUAGES ${RYTHE_LANGUAGE})

rythe_find_sources(sources "${PROJECT_SOURCE_DIR}/src")
add_library(core ${RYTHE_LIBRARY_TYPE} ${sources})

rythe_add_third_party(
	CURRENT core
	LIBRARY spdlog
	LIBRARY_HEADER_ONLY
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/spdlog"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/spdlog/include"
	FOLDER "third_party"
	FOLDER_TARGETS spdlog
)

rythe_add_third_party(
	CURRENT core
	LIBRARY tinygltf
	LIBRARY_HEADER_ONLY
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/tinygltf"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/"
	FOLDER "third_party/tinygltf"
	FOLDER_TARGETS tinygltf loader_example
)

set(JUST_INSTALL_CEREAL ON CACHE BOOL "" FORCE)
rythe_add_third_party(
	CURRENT core
	LIBRARY cereal
	LIBRARY_HEADER_ONLY
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/cereal"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/cereal/include"
	FOLDER "third_party"
	FOLDER_TARGETS cereal
)

rythe_add_third_party(
	CURRENT core
	LIBRARY argh
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/argh"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/argh"
	FOLDER "third_party"
	FOLDER_TARGETS argh
)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)
set(OPENCL_SDK_BUILD_OPENGL_SAMPLES OFF CACHE BOOL "" FORCE)
set(OPENCL_SDK_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(OPENCL_SDK_TEST_SAMPLES OFF CACHE BOOL "" FORCE)
rythe_add_third_party(
	CURRENT core
	LIBRARY OpenCL
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/opencl"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/opencl/external/OpenCL-Headers/"
	FOLDER "third_party/opencl"
	FOLDER_TARGETS OpenCL OpenCLUtils OpenCLUtilsCpp
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

rythe_add_third_party(
	CURRENT core
	LIBRARY tinyobjloader
	LIBRARY_HEADER_ONLY
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/tinyobj"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/tinyobj"
	FOLDER "third_party"
	FOLDER_TARGETS tinyobjloader
)

rythe_add_third_party(
	CURRENT core
	LIBRARY stb
	LIBRARY_HEADER_ONLY
	PATH "${RYTHE_DIR_ENGINE}/core/third_party/stb"
	INCLUDE "${RYTHE_DIR_ENGINE}/core/third_party/stb"
	FOLDER "third_party"
	FOLDER_TARGETS stb
)

rythe_configure_module(core)
rythe_copy_module_output(core rythe/engine/core)
