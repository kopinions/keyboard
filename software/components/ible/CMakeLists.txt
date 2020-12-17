idf_component_register(SRCS "ble.cpp"
        INCLUDE_DIRS "include"
        REQUIRES vif esp_if bt)
component_compile_options(-std=gnu++2a)