cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-g -std=c++2a")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(3rdparty/di)
if (${ENABLE_TESTS})
    add_subdirectory(tests)
    add_custom_target(units)
    add_custom_command(TARGET units
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
            COMMAND mkdir -p build && pushd build && cmake .. && popd && cmake --build build --target all && cmake --build build --target test)
endif ()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(kbd)