cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-O3 -std=c++2a -mlongcalls ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(3rdparty/di)
if (${IDE})
    add_subdirectory(tests)
endif ()

add_custom_target(units)
add_custom_command(TARGET units
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        COMMAND mkdir -p build && pushd build && cmake .. && popd && cmake --build build --target all && cmake --build build --target test)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(kbd)