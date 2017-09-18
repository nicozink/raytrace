cmake_minimum_required(VERSION 3.0)

PROJECT(libz)

add_library(libz INTERFACE)

if (MSVC)
	target_include_directories(libz
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include)

	target_link_libraries(libz
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/vs/zlibstatic.lib)
elseif (APPLE)
	target_include_directories(libz
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include)
	
	target_link_libraries(libz
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/lib/darwin/libz.a)
else()
	find_library(ZLIB REQUIRED)

	target_include_directories(libz
		INTERFACE
		${ZLIB_INCLUDE_DIR})
	
	target_link_libraries(libz
		INTERFACE
		${ZLIB_LIBRARY})
endif()
