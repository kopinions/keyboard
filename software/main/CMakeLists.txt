idf_component_register(SRCS "kbd.cpp"
        INCLUDE_DIRS "."
        REQUIRES keyboard esp_if)
component_compile_options(-std=gnu++2a)