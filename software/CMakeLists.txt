cmake_minimum_required(VERSION 3.14)
project(kbd C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS, ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(elf_file ${CMAKE_PROJECT_NAME}.elf)
message(STATUS ${CMAKE_CXX_COMPILER_ID})
add_executable(${elf_file})
target_sources(${elf_file} PRIVATE main/kbd.cpp)
target_compile_features(${elf_file} PUBLIC cxx_std_17)
target_compile_options(${elf_file} PUBLIC "$<$<NOT:$<CXX_COMPILER_ID:AppleClang>>:-mlongcalls>")
target_compile_options(${elf_file} PUBLIC "$<$<CXX_COMPILER_ID:AppleClang>:-mlong-calls>")
target_compile_options(${elf_file} PUBLIC "$<$<CONFIG:DEBUG>:-g3>")
target_compile_options(${elf_file} PUBLIC "$<$<CONFIG:RELEASE>:-O2>")


if("${TARGET}" STREQUAL "esp32")
    # Include for ESP-IDF build system functions
    include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
    # Create idf::esp32 and idf::freertos static libraries
    idf_build_executable(${elf_file})
    idf_build_process(esp32
            # try and trim the build; additional components
            # will be included as needed based on dependency tree
            #
            # although esptool_py does not generate static library,
            # processing the component is needed for flashing related
            # targets and file generation
            COMPONENTS esp32 freertos esptool_py
            SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
            BUILD_DIR ${CMAKE_BINARY_DIR})

else()
    # Create stubs for esp32 and freertos, stub::esp32 and stub::freertos
    add_subdirectory(stubs/esp_common)
    add_subdirectory(stubs/esp32)
    add_subdirectory(stubs/freertos)
    add_subdirectory(stubs/spi_flash)
    add_subdirectory(stubs/nvs_flash)
endif()
target_link_libraries(${elf_file} idf::esp_common idf::esp32 idf::freertos idf::spi_flash idf::nvs_flash)
#include_directories(3rdparty/di)
#add_subdirectory(components/vif)
#add_subdirectory(components/esp_if)
#add_subdirectory(components/ible)
#add_subdirectory(components/ihid)
#add_subdirectory(components/keyboard)
#add_subdirectory(components/supporting)
