add_library(stub_esp_timer INTERFACE)
target_include_directories(stub_esp_timer INTERFACE include)
add_library(idf::esp_timer ALIAS stub_esp_timer)
