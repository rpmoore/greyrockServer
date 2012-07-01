cmake_minimum_required (VERSION 2.6)
project (greyrockServer)

#set the binary dir to _build
set (PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/_build")
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

#set the version information
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(greyrockServer net_sock.cxx main.cxx)
