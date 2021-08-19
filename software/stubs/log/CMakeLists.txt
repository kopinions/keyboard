add_library(stub_log STATIC)
target_include_directories(stub_log PUBLIC include)
target_sources(stub_log PRIVATE src/esp_log.c)
add_library(idf::log ALIAS stub_log)
