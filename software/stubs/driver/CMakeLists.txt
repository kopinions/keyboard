add_library(stub_driver INTERFACE)
target_include_directories(stub_driver INTERFACE include)
add_library(idf::driver ALIAS stub_driver)
