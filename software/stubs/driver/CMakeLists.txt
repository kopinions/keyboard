add_library(stub_driver INTERFACE)
target_include_directories(stub_driver INTERFACE include)
target_link_libraries(stub_driver INTERFACE idf::esp_common)
add_library(idf::driver ALIAS stub_driver)
