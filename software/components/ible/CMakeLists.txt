idf_component_register(SRCS src/ble.cpp src/specification.cpp src/visitors.cpp src/builders.cpp src/gatt_if.cpp
        INCLUDE_DIRS "include"
        REQUIRES vif esp_if bt)

component_compile_options(-std=gnu++2a)