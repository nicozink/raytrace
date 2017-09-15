cmake_minimum_required(VERSION 3.0)

PROJECT(json_tests VERSION 1.0.0)

enable_testing()

set(SRC_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/include/json/json.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/json.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_lexer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_lexer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_parser.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_token.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/json_value.cpp)

set(SRC_TEST
	${CMAKE_CURRENT_SOURCE_DIR}/test/test_parse.cpp)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

foreach(_source IN ITEMS ${SRC_MAIN} ${SRC_TEST})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(json ${SRC_MAIN})

target_include_directories(json
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(unittest REQUIRED)

add_library(json_tests ${SRC_TEST})

target_link_libraries(json_tests json unittest)

add_executable(json_test ${SRC_TEST})

target_link_libraries(json_test json unittest)

add_test(NAME json_test
	COMMAND json_test)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${version_config}" COMPATIBILITY SameMajorVersion)
configure_package_config_file("cmake/Config.cmake.in" "${project_config}" INSTALL_DESTINATION "${config_install_dir}")

install(TARGETS json EXPORT jsonTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include)
install(DIRECTORY include/json DESTINATION include)
install(EXPORT jsonTargets
	FILE jsonTargets.cmake
	DESTINATION lib/cmake/json)
install(
	FILES "${project_config}" "${version_config}"
	DESTINATION "${config_install_dir}"
)
