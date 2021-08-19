cmake_minimum_required(VERSION 3.14)

enable_testing()

macro(unit TESTNAME)
    add_executable(${TESTNAME}.ut ${ARGN})
    add_test(${TESTNAME}.ut ${TESTNAME}.ut)
    target_link_libraries(${TESTNAME}.ut PRIVATE kbd::vif kbd::supporting)
    target_include_directories(${TESTNAME}.ut PRIVATE ${CMAKE_CURRENT_LIST_DIR}/common)
    target_include_directories(${TESTNAME}.ut PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/di)
endmacro()

macro(functional TESTNAME)
    add_executable(${TESTNAME}.ft ${ARGN})
    add_test(${TESTNAME}.ft ${TESTNAME}.ft)
    target_link_libraries(${TESTNAME}.ft PRIVATE kbd::vif kbd::supporting)
    target_include_directories(${TESTNAME}.ft PRIVATE ${CMAKE_SOURCE_DIR}/tests/common)
    target_include_directories(${TESTNAME}.ft PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/di)
endmacro()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -include ${CMAKE_CURRENT_LIST_DIR}/common/test.hpp")
add_subdirectory(units)
#add_subdirectory(functions)