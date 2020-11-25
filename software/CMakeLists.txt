cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-O3 -std=c++2a -mlongcalls ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(3rdparty/di)
#add_subdirectory(tests)

add_custom_target(tests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        COMMAND mkdir -p build && pushd build && cmake .. && popd && cmake --build build --target all && cmake --build build --target test)

add_custom_target(format
        COMMAND find ${CMAKE_CURRENT_LIST_DIR}/main ${CMAKE_CURRENT_LIST_DIR}/components ${CMAKE_CURRENT_LIST_DIR}/tests -iname "*.cpp" -or -iname "*.hpp" | xargs clang-format -i)

add_custom_target(format-changed ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND git status -s --porcelain=v2 |awk '{print $$NF}' | grep -E "\\.cpp\\|\\.hpp" | xargs clang-format -i)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(kbd)