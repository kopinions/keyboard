cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_FLAGS "-O3 -std=gnu++2a -mlongcalls -fconcepts ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(3rdparty/di)

add_custom_target(format
        COMMAND find ${CMAKE_CURRENT_LIST_DIR}/main ${CMAKE_CURRENT_LIST_DIR}/components ${CMAKE_CURRENT_LIST_DIR}/tests -iname "*.cpp" -or -iname "*.hpp" | xargs clang-format -i)

add_custom_target(format-changed ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND git status -s --porcelain=v2 |awk '{print $$NF}' | grep -E "\\.cpp\\|\\.hpp" | xargs clang-format -i)

add_custom_target(ptests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/portables
        COMMAND mkdir -p build && pushd build && cmake .. && popd && cmake --build build --target all && cmake --build build --target test)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(kbd)