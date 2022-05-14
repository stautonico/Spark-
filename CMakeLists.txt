cmake_minimum_required(VERSION 3.20)

project(spark LANGUAGES C CXX ASM)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/toolchain.cmake)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "")

    message(FATAL_ERROR "We don't support release builds yet. Please use Debug instead.")

endif ()
add_subdirectory(src/kernel)