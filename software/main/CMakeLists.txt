idf_component_register(SRCS "kbd.cpp"
        INCLUDE_DIRS "."
        REQUIRES keyboard esphal)
component_compile_options(-std=gnu++2a)