cmake_minimum_required(VERSION 3.10)

set(NAME jsonlib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${NAME} VERSION 1.0.0 LANGUAGES C)

# Grab All  Source Files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/project/*.c")

message("Message ${SOURCE_FILES}")

# Add source files for the executable
add_library(${NAME} SHARED
    ${SOURCE_FILES}
)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set_target_properties(${NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${NAME} PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/project/include/json/json.h)

target_include_directories(${NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/project/include
)

install(TARGETS ${NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

