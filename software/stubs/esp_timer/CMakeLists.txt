add_library(stub_esp_timer STATIC)
target_include_directories(stub_esp_timer PUBLIC include)
target_sources(stub_esp_timer PRIVATE src/esp_timer.cpp)
add_library(idf::esp_timer ALIAS stub_esp_timer)
