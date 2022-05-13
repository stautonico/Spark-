cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/toolchain.cmake)

project(spark LANGUAGES C CXX ASM)

add_subdirectory(src/kernel)