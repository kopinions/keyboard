add_library(stub_nvs_flash INTERFACE)
target_include_directories(stub_nvs_flash INTERFACE .)
add_library(idf::nvs_flash ALIAS stub_nvs_flash)
