cmake_minimum_required(VERSION 3.10)

set(NAME jsonlib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
add_link_options(-fsanitize=address)

project(${NAME} VERSION 1.0.0 LANGUAGES C)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
# Grab All  Source Files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/project/*.c")

# Add source files for the executable
add_library(${NAME} SHARED
    ${SOURCE_FILES}
)

set_target_properties(${NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/project/include)
