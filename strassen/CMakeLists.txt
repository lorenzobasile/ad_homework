cmake_minimum_required (VERSION 2.6)
project (strassen)

set(CMAKE_BUILD_TYPE Release)

FILE (GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c"
	               "${PROJECT_SOURCE_DIR}/include/*.h")

include_directories("${PROJECT_SOURCE_DIR}/include")

SET(${LIB_REQUIRED_LIBRARIES} "")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

add_executable (strassen_test ${SOURCES})

