idf_component_register(SRCS src/chrono_if.cpp src/esp_log_sink.cpp src/gpio_if.cpp src/gpios_if.cpp src/scheduler_if.cpp
        INCLUDE_DIRS "include"
        REQUIRES vif)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=c++17)