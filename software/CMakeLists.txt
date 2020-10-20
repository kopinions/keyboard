cmake_minimum_required(VERSION 3.14)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -std=c++2a")
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(ENV{IDF_PATH} /Volumes/data/workspace/1si/iot/esp-idf)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(kbd)

