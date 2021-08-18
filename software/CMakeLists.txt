cmake_minimum_required(VERSION 3.14)
project(kbd C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if ("${TARGET}" STREQUAL "esp32")
    include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
    # Create idf::esp32 and idf::freertos static libraries
    idf_build_executable(${elf_file})
    idf_build_process(esp32
            COMPONENTS esp32 freertos esptool_py
            SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
            BUILD_DIR ${CMAKE_BINARY_DIR})
else ()
    # Create stubs for esp32 and freertos, stub::esp32 and stub::freertos
    add_subdirectory(stubs/esp_common)
    add_subdirectory(stubs/esp32)
    add_subdirectory(stubs/esp_timer)
    add_subdirectory(stubs/log)
    add_subdirectory(stubs/driver)
    add_subdirectory(stubs/bt)
    add_subdirectory(stubs/freertos)
    add_subdirectory(stubs/spi_flash)
    add_subdirectory(stubs/nvs_flash)
endif ()

add_subdirectory(components/vif)
add_subdirectory(components/esp_if)
add_subdirectory(components/ible)
add_subdirectory(components/ihid)
add_subdirectory(components/keyboard)
add_subdirectory(components/supporting)
add_subdirectory(src)