cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-g -std=c++17")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
project(kbd_test)

enable_testing()

macro(unit TESTNAME)
    add_executable(${TESTNAME}.ut ${ARGN})
    add_test(${TESTNAME}.ut ${TESTNAME}.ut)
endmacro()

macro(functional TESTNAME)
    add_executable(${TESTNAME}.ft ${ARGN})
    add_test(${TESTNAME}.ft ${TESTNAME}.ft)
endmacro()

include_directories(.)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../components/vif)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../components/keyboard)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/../components/supporting/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../3rdparty/di)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -include ${CMAKE_CURRENT_LIST_DIR}/common/test.hpp")
add_subdirectory(units)
add_subdirectory(functions)



project(tests)