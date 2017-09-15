cmake_minimum_required(VERSION 3.0)

PROJECT(json_tests)

enable_testing()

include(json.cmake)

file(
	GLOB_RECURSE SRC_TEST
	LIST_DIRECTORIES false
	${CMAKE_CURRENT_SOURCE_DIR}/test/*.c*
)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

foreach(_source IN ITEMS ${SRC_TEST})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

ADD_EXECUTABLE(
	json_tests
	${SRC_TEST})

find_package(unittest REQUIRED)

target_link_libraries(json_tests json unittest)

add_test(NAME MyTest
         COMMAND json_tests)