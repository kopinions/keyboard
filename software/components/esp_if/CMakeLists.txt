#idf_component_register(SRCS src/chrono_if.cpp src/esp_log_sink.cpp src/gpio_if.cpp src/gpios_if.cpp
#        INCLUDE_DIRS "include"
#        REQUIRES vif)
add_library(esp_if)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=c++17)