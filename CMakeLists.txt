cmake_minimum_required(VERSION 3.10)

set(LIBNAME jsonlib)
project(${LIBNAME} VERSION 3.0 LANGUAGES C)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/project/source/*.c")

add_library(${LIBNAME} SHARED ${SOURCE_FILES})

target_include_directories(${LIBNAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/project/include/")
