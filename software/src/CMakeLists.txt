target_sources(${elf_file} PRIVATE
        kbd.cpp
        ../components/link/src/message.cpp
        ../components/link/src/link.cpp
        ../components/link/src/link_control.cpp)
target_compile_features(${elf_file} PUBLIC cxx_std_17)
target_compile_options(${elf_file} PUBLIC "$<$<NOT:$<CXX_COMPILER_ID:AppleClang>>:-mlongcalls>")
target_compile_options(${elf_file} PUBLIC "$<$<CXX_COMPILER_ID:AppleClang>:-mlong-calls>")
target_compile_options(${elf_file} PUBLIC "$<$<CONFIG:DEBUG>:-g3>")
target_compile_options(${elf_file} PUBLIC "$<$<CONFIG:RELEASE>:-O2>")
target_include_directories(${elf_file} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${elf_file} PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/di)
target_link_libraries(${elf_file} idf::esp_common idf::esp32 idf::freertos idf::spi_flash idf::nvs_flash idf::bt)
target_link_libraries(${elf_file} kbd::esp_if kbd::ible kbd::ihid kbd::kbd kbd::supporting kbd::link)