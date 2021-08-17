add_library(stub_esp_common INTERFACE)
target_include_directories(stub_esp_common INTERFACE .)
add_library(idf::esp_common ALIAS stub_esp_common)
