idf_component_register(
        SRCS
        src/keyboard.cpp
        src/layout.cpp
        src/matrix.cpp
        src/config.cpp
        INCLUDE_DIRS "include")

target_link_libraries(vif)

component_compile_options(-std=c++17)
