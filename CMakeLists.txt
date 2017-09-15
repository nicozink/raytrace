cmake_minimum_required(VERSION 3.5)

PROJECT(render)

enable_testing()

MACRO(FILELIST result directory pattern)
	file(
		GLOB
		files
		RELATIVE ${directory}
		${directory}/${pattern})

	SET(${result} "")

	foreach(_file  IN ITEMS ${files})
		LIST(APPEND ${result} ${_file})
	endforeach()
ENDMACRO()

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

file(
	GLOB_RECURSE SRC_MAIN
	LIST_DIRECTORIES false
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*
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

set(LINKS "")

FILELIST(DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/dependencies *)

foreach(_dependency IN ITEMS ${DEPENDENCIES})
	if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/include)
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/include)
	endif()

	if (MSVC)
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/vs)
			link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/vs)

			FILELIST(LINK_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/vs *.lib)

			foreach(_lib IN ITEMS ${LINK_LIBS})
				LIST(APPEND LINKS ${_lib})
			endforeach()
		endif()
	elseif (APPLE)
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/darwin)
			link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/darwin)

			FILELIST(LINK_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${_dependency}/lib/darwin *.a)

			foreach(_lib IN ITEMS ${LINK_LIBS})
				LIST(APPEND LINKS ${_lib})
			endforeach()
		endif()
	endif()
endforeach()

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

TARGET_LINK_LIBRARIES(render json ${LINKS})
