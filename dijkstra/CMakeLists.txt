cmake_minimum_required (VERSION 2.56)
project (dijkstra)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

FILE (GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c"
	               "${PROJECT_SOURCE_DIR}/include/*.h")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable (dijkstra ${SOURCES})

if(BINHEAP_PATH)
	message("Linking binheap library")
	add_library(binheap SHARED IMPORTED) 

	set_target_properties(binheap PROPERTIES
  		IMPORTED_LOCATION "${BINHEAP_PATH}/libbinheap.so"
  		INTERFACE_INCLUDE_DIRECTORIES "${BINHEAP_PATH}/include/"
	)

	target_link_libraries(dijkstra "binheap")
endif(BINHEAP_PATH)


