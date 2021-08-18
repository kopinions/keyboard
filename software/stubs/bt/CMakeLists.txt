add_library(stub_bt INTERFACE)
target_include_directories(stub_bt INTERFACE include)
target_link_libraries(stub_bt INTERFACE idf::esp_common)
add_library(idf::bt ALIAS stub_bt)
