cmake_minimum_required(VERSION 3.0)

PROJECT(libpng)

add_library(libpng INTERFACE)

target_include_directories(libpng
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
	target_link_libraries(libpng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/vs/libpng16_static.lib)
elseif (APPLE)
	target_link_libraries(libpng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/darwin/libpng.a)
endif()

target_link_libraries(libpng INTERFACE libz)
