add_custom_target(ut
        COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 ${CMAKE_CTEST_COMMAND} -R ".*\\.ut$$"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

macro(unit TESTNAME)
    add_executable(${TESTNAME}.ut ${ARGN})
    add_dependencies(ut ${TESTNAME}.ut)
    add_test(${TESTNAME}.ut ${TESTNAME}.ut)
    target_link_libraries(${TESTNAME}.ut PRIVATE kbd::vif kbd::supporting)
    target_link_libraries(${TESTNAME}.ut PRIVATE testing)
    target_include_directories(${TESTNAME}.ut PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/di)
endmacro()

macro(functional TESTNAME)
    add_executable(${TESTNAME}.ft ${ARGN})
    add_test(${TESTNAME}.ft ${TESTNAME}.ft)
    target_link_libraries(${TESTNAME}.ft PRIVATE kbd::vif kbd::supporting)
    target_link_libraries(${TESTNAME}.ft PRIVATE testing)
    target_include_directories(${TESTNAME}.ft PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/di)
endmacro()


add_subdirectory(common)
add_subdirectory(units)
#add_subdirectory(functions)