add_library(stub_bt STATIC)
target_sources(stub_bt PRIVATE src/esp_bt_main.c src/esp_gap_ble_api.c
        src/esp_gatts_api.c)
target_include_directories(stub_bt PUBLIC include)
target_link_libraries(stub_bt PUBLIC idf::esp_common)
add_library(idf::bt ALIAS stub_bt)
