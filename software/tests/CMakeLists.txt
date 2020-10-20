cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-g -std=c++2a")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
project(kbd_test)

enable_testing()

macro(unit TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    add_test(${TESTNAME} ${TESTNAME})
endmacro()

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -include common/test.hpp")
add_subdirectory(units)