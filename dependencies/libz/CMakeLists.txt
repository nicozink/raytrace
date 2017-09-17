cmake_minimum_required(VERSION 3.0)

PROJECT(libz)

add_library(libz INTERFACE)

target_include_directories(libz
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
	target_link_libraries(libz INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/vs/zlibstatic.lib)
elseif (APPLE)
	target_link_libraries(libz INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/darwin/libz.a)
endif()
