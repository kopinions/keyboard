enable_testing()

macro(unit TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
endmacro()

include_directories(.)
if(MSVC)
    add_definitions(/FI"common/test.hpp")
else()
    # GCC or Clang
    add_definitions(-include common/test.hpp)
endif()
add_subdirectory(units)