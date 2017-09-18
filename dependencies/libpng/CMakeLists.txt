cmake_minimum_required(VERSION 3.0)

PROJECT(libpng)

add_library(libpng INTERFACE)

if (MSVC)
	target_include_directories(libpng
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include)

	target_link_libraries(libpng
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/vs/libpng16_static.lib)
elseif (APPLE)
	target_include_directories(libpng
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include)

	target_link_libraries(libpng
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/darwin/libpng.a)
else()
	find_package(PNG REQUIRED)

	target_include_directories(libpng
		INTERFACE
		${PNG_INCLUDE_DIR})
	
	target_link_libraries(libpng
		INTERFACE
		${PNG_LIBRARY})
endif()

target_link_libraries(libpng INTERFACE libz)
