idf_component_register(SRCS src/ble.cpp src/specification.cpp
        INCLUDE_DIRS "include"
        REQUIRES vif esp_if bt)

component_compile_options(-std=gnu++2a)