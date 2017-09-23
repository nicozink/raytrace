cmake_minimum_required(VERSION 3.5)

PROJECT(render)

enable_testing()

# Define enumerators to identify system properties. These
# need to match with the definitions found in the file
# "Globals.h".

# Define the operating system types.
set(WINDOWS_ENUM 0)
set(UNIX_ENUM 1)

# Define the compiler types.
set(GCC_ENUM 2)
set(MINGW_ENUM 3)
set(VISUAL_STUDIO_ENUM 4)
set(CLANG_ENUM 5)

# Define the render systems.
set(SDL_ENUM 5)
set(GLX_ENUM 6)

# Define the architecture.
set(X86_ENUM 7)
set(X64_ENUM 8)

# Detect the operating system.
if (WIN32)
    set(OPERATING_SYSTEM ${WINDOWS_ENUM})
elseif (UNIX)
    set(OPERATING_SYSTEM ${UNIX_ENUM})
else (WIN32)
    message(FATAL_ERROR "An unknown operating system is being used." )
endif (WIN32)

# Detect the compiler.
if (MSVC)
	set(COMPILER ${VISUAL_STUDIO_ENUM})
elseif (MINGW)
	set(COMPILER ${MINGW_ENUM})
elseif (CMAKE_COMPILER_IS_GNUCC)
	set(COMPILER ${GCC_ENUM})
elseif (APPLE)
	set(COMPILER ${CLANG_ENUM})
else (MSVC)
	message(FATAL_ERROR "An unknown compiler is being used." )
endif (MSVC)

# Set user specified flags.
if (MSVC)
set(CMAKE_CXX_FLAGS "-std=c++11 -D_USE_MATH_DEFINES")
else ()
set(CMAKE_CXX_FLAGS "-DDEBUG -g -Wall -O0 -std=c++11")
endif()

set(SRC_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/quadratic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/quadratic.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/vector.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/vector.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/vector3d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/math/vector3d.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_lexer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_lexer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_parser.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_shader.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_shader_type.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/osl/osl_token.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/color.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/color.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/color_accumulator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/color_accumulator.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/intersection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/intersection.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/ray.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/primitive/ray.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/batch_render.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/batch_render.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/render_job.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/render_job.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/resource/image.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/resource/image.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/resource/image_utilities.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/resource/image_utilities.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/flat_color.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/flat_color.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/material.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/material.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/surface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/surface.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/material/texture.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/cube_map.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/cube_map.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/light.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/light.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/light_type.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/light_type.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/plane.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/plane.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/point_light.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/point_light.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/sphere.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/sphere.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/sphere_light.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/sphere_light.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/traceable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/traceable.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/triangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/object/triangle.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/camera.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/scene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/scene.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/scene_reader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/world/scene_reader.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/render.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/render.h
)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

foreach(_source IN ITEMS ${SRC_MAIN})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

# Output the version to the Version.h file.
configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/src/system.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/src/system.h"
)

set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/render/")
set(WORKSPACE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/examples/")
set(OUTPUT_PATH "./")

# Output the config to the config.json file.
configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/resources/config.json.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.json"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(dependencies/libpng)
add_subdirectory(dependencies/libz)

ADD_EXECUTABLE(
	render
	${SRC_MAIN})

set(CMAKE_PREFIX_PATH "/libraries")
set(as_subproject json unittest)

macro(find_package name)
	if(NOT "${name}" IN_LIST as_subproject)
		_find_package(${ARGV})
	endif()
endmacro()

add_subdirectory(libraries/json)
add_subdirectory(libraries/unittest)

TARGET_LINK_LIBRARIES(render json libpng libz Threads::Threads)

add_custom_command(TARGET render POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_BINARY_DIR}/config.json
	$<TARGET_FILE_DIR:render>/config.json)
